import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    with open(sys.argv[1], 'r') as f:
        reader = csv.DictReader(f)
        dna = list(reader)
    dictn = {}
    for row in dna:
        for key in row:
            if key != 'name':
                dictn[key] = 0

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as f:
        sequence = f.read()

    for person in dna:
        for key, value in person.items():
            if key != 'name':
                person[key] = int(value)

    # TODO: Find longest match of each STR in DNA sequence
    strv = len(dictn) - 1
    keyl = len(list(dictn.keys())[strv])
    seql = len(sequence)
    keyn = list(dictn.keys())[strv]
    perm = 0

    for i in range(strv + 1):
        temp = list(dictn.keys())[i]
        p = longest_match(sequence, temp)
        dictn[temp] = p

    # TODO: Check database for matching profiles
    keys = list(dictn.keys())
    for item in dna:
        match = True
        for key, value in item.items():
            if key in dictn and value != dictn[key]:
                match = False
                break
        if match:
            print(item['name'])
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
