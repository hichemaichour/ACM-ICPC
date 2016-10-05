int fromDecimal(int n, int b)
{
   int result=0;
   int multiplier=1;
      
   while(n>0)
   {
      result+=n%b*multiplier;
      multiplier*=10;
      n/=b;
   }
      
   return result;
}

int toDecimal(int n, int b)
{
   int result=0;
   int multiplier=1;
      
   while(n>0)
   {
      result+=n%10*multiplier;
      multiplier*=b;
      n/=10;
   }
      
   return result;
}