import os

from datetime import datetime
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    portfolio = db.execute("SELECT * FROM stocks WHERE userid = ? AND qty > 0",session["user_id"])
    sum = 0
    for stock in portfolio:
        sum = sum + stock['amount']
        stock['price'] = usd(stock['price'])
        stock['amount'] = usd(stock['amount'])

    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    return render_template("index.html", portfolio=portfolio, balance=usd(user[0]['cash']), total=usd(sum))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get stock quote
        stock = request.form.get("symbol")
        qty1 = request.form.get("shares")
        if not qty1:
            return apology("Enter a valid qty", 400)

        # Handling non-numeric shares
        try:
            qty = int(qty1)
        except ValueError:
            return apology("Enter a valid qty. Only integers are allowed", 400)

        # Handling negative shares
        if qty < 1:
            return apology("Enter a valid qty. Only positive integers are allowed", 400)

        if not stock:
            return apology("must provide stock", 400)
        else:
            quote = lookup(stock)
            if not quote:
                return apology("invalid stock", 400)
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
            total = float(quote['price'] * qty)
            balance = user_cash[0]['cash'] - total
            if (balance < 0):
                return apology("insuficient balance", 400)
            else:
                db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

                now = datetime.now()
                db.execute("INSERT INTO history (userid, year, month, day, hour, minute, activity, name, price, qty) VALUES (?,?,?,?,?,?,?,?,?,?)",session["user_id"], now.year, now.month, now.day, now.hour, now.minute, "Buy", quote['symbol'], quote['price'], qty)
                holding = db.execute("SELECT * FROM stocks WHERE userid = ? AND stock = ?", session["user_id"], quote['symbol'])
                user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
                if not holding:
                    db.execute("INSERT INTO stocks (userid, stock, qty, price, amount, name) VALUES(?,?,?,?,?,?)",session["user_id"], quote['symbol'], qty, quote['price'], total, quote['name'])
                else:
                    shares = holding[0]['qty'] + qty
                    avg = (holding[0]['amount'] + total) / shares
                    amount = shares * avg
                    db.execute("UPDATE stocks SET qty = ?, price = ?, amount = ? WHERE userid = ? AND stock = ?", shares, avg, amount, session["user_id"], quote['symbol'] )
                return redirect(url_for("success", name=quote['name'], price=usd(quote['price']), symbol=quote['symbol'], shares=qty, total=usd(total), cash=usd(user[0]['cash']), original=usd(user_cash[0]['cash'])))

    else:
        return render_template("buy.html")

@app.route("/success")
@login_required
def success():
    name = request.args.get("name")
    price = request.args.get("price")
    symbol = request.args.get("symbol")
    shares = request.args.get("shares")
    total = request.args.get("total")
    original = request.args.get("original")
    cash = request.args.get("cash")

    return render_template("success.html", name=name, price=price, symbol=symbol, shares=shares, total=total, original=original, cash=cash)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    portfolio = db.execute("SELECT * FROM history WHERE userid = ?",session["user_id"])
    for stock in portfolio:
        stock['price'] = usd(stock['price'])
    return render_template("history.html", portfolio=portfolio)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Get stock quote
        stock = request.form.get("symbol")
        if not stock:
            return apology("must provide stock", 400)
        else:
            quote = lookup(stock)
            if not quote:
                return apology("invalid stock", 400)
            return render_template("quote.html", name=quote['name'], price=usd(quote['price']), symbol=quote['symbol'])
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)
        if not request.form.get("password"):
            return apology("must provide password", 400)
        # Ensure password was submitted
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("password not match", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 0:
            return apology("username already exist", 400)

        hash = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES (?,?)",request.form.get("username"), hash)

        row = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        session["user_id"] = row[0]["id"]
        # Redirect user to home page
        return redirect(url_for("index"))

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Get stock quote
        stock = request.form.get("symbol")
        qty1 = request.form.get("shares")
        if not qty1:
            return apology("Enter a valid qty", 400)
        qty = int(qty1)
        if qty < 1:
            return apology("Enter a valid qty", 403)
        if not stock:
            return apology("must provide stock", 400)
        else:
            quote = lookup(stock)
            if not quote:
                return apology("invalid stock", 400)
            user_cash = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
            holding = db.execute("SELECT * FROM stocks WHERE userid = ? AND stock = ?", session["user_id"], quote['symbol'])
            if not holding:
                return apology("stocks not avaiable", 400)
            if (holding[0]['qty'] < qty):
                return apology("insuficient qty", 400)
            else:
                total = float(quote['price'] * qty)
                balance = user_cash[0]['cash'] + total
                db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, session["user_id"])

                now = datetime.now()
                db.execute("INSERT INTO history (userid, year, month, day, hour, minute, activity, name, price, qty) VALUES (?,?,?,?,?,?,?,?,?,?)",session["user_id"], now.year, now.month, now.day, now.hour, now.minute, "Sell", quote['symbol'], quote['price'], qty)
                user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
                shares = holding[0]['qty'] - qty
                amount = holding[0]['price'] * shares
                db.execute("UPDATE stocks SET qty = ?, amount = ? WHERE userid = ? AND stock = ?", shares, amount, session["user_id"], quote['symbol'] )
                return redirect(url_for("success", name=quote['name'], price=usd(quote['price']), symbol=quote['symbol'], shares=qty, total=usd(total), cash=usd(user[0]['cash']), original=usd(user_cash[0]['cash'])))

    else:
        symbols = db.execute("SELECT stock FROM stocks where userid = ?", session["user_id"])
        return render_template("sell.html", symbols=symbols)


