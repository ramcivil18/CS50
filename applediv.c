#include <stdio.h>

long long min (long long a, long long b)
{
  return (a < b) ? a : b;
}
int main(void)
{
  long long array[20];
  int n;
  scanf("%d",&n);
  long long sum = 0;
  long long i,j;
  for(i = 0; i < n; i++)
  {
    scanf("%lld",&array[i]);
    sum += array[i];
  }
  long long d = 20 * 1e9;
  long long answer = 0;

  for(i = 0; i < (1<<n); i++)
  {
    long long cur = 0;
    for(j = 0; j < n; j++)
    {
      if(i & (1<<j))
      {
        cur += array[j];

      }
    }
    long long cur1 = ((sum - cur) - cur);
    if (cur1 >= 0)
    {
      d = min(d, cur1);
    }
  }
  printf("%lld\n", d);
  return 0;
}
