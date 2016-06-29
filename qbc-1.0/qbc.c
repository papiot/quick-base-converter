/*
               Author: Catalin Avram
	       email: catalin_avram@hotmail.com
	       
	       Authorship:  The code has entirely been written by Catalin Avram.  Ideas have been
	       used from the following references:

	       1. The C Programming Language, K+R
	       2. The Linux Documentation Project (www.tldp.org)
	       
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define digits "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define BUFFSIZE 1024

unsigned long  in_base;
unsigned long  out_base;


int num_operands(char* c)
{
  int i = 1;

  while (*c != '\0')
  {
    if (*c == ',') i++;
    c++;
  }
  
  return (i);
}
/*=============================================*/
char* get_operand(char* c, int x)
{
  int i;
  char* ret;
  i=0;
  ret = (char *) malloc(100);

  if (x)
  {
    c = strchr(c, ',');
    c++;
    ret = strncpy(ret, c, strlen(c) - 2);

    
    return(ret);
  }
  else
  {
    
    while (*c != ',')
    {
      *ret = *c;
      ret++; c++; i++;
    }
    
    *ret = '\0';
    ret -= i;

    
    return(ret);
  }


  
}

/*===============================================*/
int case_validity(char* c)
{
  int flag = 0;
  while(*c != '\0')
  {
    if(strchr(digits, *c) == NULL)
    {
      if(*c == ',')
      {
	flag = 1; c++; continue;
      }
      

      /*if(*c == '=') return(1);*/
      if(flag && (*c == '+') && (*(c+1) == '=')) return(2);
      if(flag && (*c == '-') && (*(c+1) == '=')) return(3);
      if(flag && (*c == 'x') && (*(c+1) == '=')) return(4);
      if(flag && (*c == '/') && (*(c+1) == '=')) return(5);
      if(!flag && (*c == '=')) return(1);

      /*if here, case invalid*/
      return (0);
    }
    else 
    {
      c++;
    }
  }
}

/*===============================================*/
void reverse(char* x)
{
  int n;
  char* c;
  
  int i;
  
 
  n = strlen(x);
  
  c = (char *) malloc(n);
  
  while ((*c = *x) != '\0')
  {
    c++;
    x++;
  }
  c--;
  x -= n;
  
  
  for (i = 0; i < n; i++)
  {
    *x = *c;
    
    x++; 
    c--;
  }
  
  
}
/*==============================================*/
void r_process_value(char* x, int base, unsigned long* val)
{
  unsigned long  i;
  unsigned long  r;
  char* c = "";
  
  /* Trying to fix the overloaing problem*/
  /*if (*val > 4294967295)        /* <--  FIX ME!!!  */
   /*val-= 4294967295;*/
  
  i = *val / base;
  
  r = *val % base;
  *val = *val / base;
  if (i != 0)
  {
    *x = digits[r];
    x++;
    r_process_value(x, base, val);
  }
  else
  {
    *x = digits[r];
  }
  

  
  
}
/*==============================================*/
void helper(char** cases, int base, unsigned long val)
{
  unsigned long tmp;
   char* dummy;
     
   dummy = malloc(100 * sizeof(char));
   
   r_process_value(dummy,in_base, &val);
   reverse(dummy);
           
   tmp = strlen(dummy);
   dummy += tmp;
   *dummy = '=';
   dummy++;
   *dummy = '\0';
   dummy -= tmp+1;

   *cases = dummy;
}
/*==============================================*/
void helper1(char** cases, int base, unsigned long val, unsigned long val1, int j)
{
  unsigned long tmp;
  char* dummy;
  char* rummy;
  int t;
     
  dummy = malloc(50 * sizeof(char));
  rummy = malloc(50 * sizeof(char));

  r_process_value(dummy, in_base, &val);
  reverse(dummy);
  t = strlen(dummy);
  dummy += t;
  *dummy = ',';
  dummy -= t;

  /*  printf("%s\t%s\n" , "dummy:  ", dummy);*/
 
  r_process_value(rummy, in_base, &val1);
  reverse(rummy);
  t = strlen(rummy);
  rummy += t;
  *rummy = '\0';
  rummy -= t;
  
  /*  printf("%s\t%s\n" , "rummy:  ", rummy);*/

  strcat(dummy, rummy);
  /*  printf("%s\n", dummy);*/
  
  *cases = dummy;


 t = strlen(*cases);
 cases[0] += t;
 switch (j)
 {
    case 2:
    {
      *cases[0] = '+';
      break;
    }
    case 3:
    {
      *cases[0] = '-';
      break;
    }
    case 4:
    {
      *cases[0] = 'x';
      break;
    }
    case 5:
    {
      *cases[0] = '/';
      break;
    }
 }
 
 cases[0]++;
 *cases[0] = '=';
 cases[0]++;
 *cases[0] = '\0';
 cases[0] -= t + 2;

  /*  printf ("%s\t%s\n", "*cases:", *cases);*/


}
/*==============================================*/
void compute_output(int num_cases, char* cases[], char* out[])
{
  unsigned long val;
  unsigned long val1;
  unsigned long total;
 
  unsigned long* tp;
  
  int i;
  int j, t;
  char* temp;
  unsigned long q, r;

  char* c;
  tp = &total;
  c = (char *) malloc(100);
  temp = (char *) malloc(100);


  


  for (i = 0; i < num_cases; i++)
  {
    j = case_validity(cases[i]);
     
    if (j)
    {

      if (j == 1)
      {
	
	   process_value(cases[i], in_base, &val);	  
	 
	   helper(&cases[i], in_base, val); 
	  	   
	   r_process_value(out[i], out_base, &val);
	   reverse(out[i]);
	   if (*out[i] == '0') *out[i] = '\0';
	   
	   
      }
      if ((j == 2) || (j == 3) || (j == 4) || (j == 5))
      {
	process_value(get_operand(cases[i], 0), in_base, &val);
        process_value(get_operand(cases[i], 1), in_base, &val1);
	helper1(&cases[i], in_base, val, val1, j);
	 
	switch(j)
	{
	   case 2:
	   {
	     total = val + val1;
	     break;
	   }
	   case 3:
	   {
	     if (val < val1) 
	       total = 0;
	     else 
	       total = val - val1;
	     break;
	   }
	   case 4:
	   {
	     total = val * val1;
	     break;
	   }
	   case 5:
	   {
	     if (val1 != 0) {
	     q = val / val1;
	     r = val % val1;
	     if (q!=0)
	     r_process_value(out[i], out_base, &q);
	     c = temp;
	     *temp = ',';
	     temp++;
	     if(r!=0)
	     r_process_value(temp, out_base, &r);
	     reverse(temp);
	     

	     reverse(out[i]);

	     out[i] = strcat(out[i], c);
	     }
	     else
	     {
	       cases[i] = "";
	       out[i] = "divide by zero";
	     }
	     break;
	   }
	}
	if (j != 5)
	{
	  if (total != 0) 
	  {
	    r_process_value(out[i], out_base, tp);
	    reverse(out[i]);
	  }
	  else
	  {
	    out[i] = "\0";
	  }
	  
	}
      }

      
    }
    else
    {
      
      cases[i] = "\0";
      out[i] = "invalid input\0";
    }
  } 
}

/*===============================================*/

void parse(int num, char* in, char* cases[])
{
  
  
  int j = 0;
  int i = 0;

  for (j = 0; j < num; j++)
  {
    do
    {
      *cases[j] = *in;
      
      in++;
      cases[j]++;
      i++;
    }
    while(*in != '=');
    
    
     *cases[j] = *in;
     cases[j]++;
     i++;
    *cases[j] = '\0';
    cases[j] -= i;
    i = 0;
    in++;
    
  }
  
}

/*===============================================*/

int n_cases(char* in)
{
  int num = 0;
  int i = 0;
  while (*in != '\0')
  {
    if (*in == '=')
    {
      num++;
    }
    i++;
    in++;
    
  }
  in -= i;
  
  return (num);
}


/*===============================================*/

void input(char *in)
{
  int flag = 0;
  int i;
  char c = 'a';
  char lastchar ='a';
  
  i = 0;
  

  

  while(!flag || (c != '\n'))
  /*while(!((lastchar == '=') && (c == '\n')))*/
  {
    /*lastchar = c;*/
    c = getchar();
    if (c == '=')
    {
	flag = 1; 
	
    }

    if (c == EOF) exit(0);
    if ((c != ' ') && (c != '\t') && (c != '\n'))
    {
      
      
      *in = c;
      in++;
      i++;
      
      
    }
    
    else 
    {
      continue;
      
    }
    
   
  }

  

  in++;
  i++;
  *in = '\0';
  
  in -= i;
  
  
}


/*===================================================================*/
/*
  returns 1 if valid, 0 if invalid. If valid, accumulates the value
*/
int process_value(char* x, int base, unsigned long * val)
{
  int i = 0;
  char *c;
  *val = 0;
  
  while ((*x != '\0') && (*x != '='))
  {
    
    for (i = 0; i < 36; i++)
    {
      if (*x == digits[i])
	break;
    }

    if (i == 36) 
     {
       *val = 0;
       return (0);
     }
    
    else
    {
      
      *val = (*val) * base + i;
      x++;
    }
  }

  /*  Overloading problem */
  /*if (*val > 4294967295)                 /*  <-- FIX ME  */
  /* (*val) -= 4294967295;*/
  return (1);
}

/*====================================================================*/
/*
  Verify the arguments
*/
int check_args(int argc, char * argv[])
{

  
  if (argc != 3)
    return(0);
  else
  {
    
   
    int x = process_value(argv[1], 10, &in_base);
    int y = process_value(argv[2], 10, &out_base);

    
    if ( !x || !y || ((int)in_base > 36) || ((int)out_base > 36) || ((int)in_base < 2) || ((int)out_base < 2)  )
      return(0);
  }
  return (1);
}

/*-------------------*/

main (int argc, char * argv[])
{
  char *in;
  int num_cases;
  char **cases;
  char **out;
  unsigned long val;
  unsigned long val1;
  char* tmp;
  char* tmp1;
  
  int j;
  
  
  in = (char *) malloc(BUFFSIZE);
  if (!(check_args(argc, argv)))
  {
    printf("%s%s%s\n", "Usage: ", argv[0], " [input_base] [output_base]");
    exit(1);
  }

  while(1) {
  input(in);

  num_cases = n_cases(in);

  cases = malloc(num_cases * sizeof(char *));
  out   = malloc(num_cases * sizeof(char *));
  

  for (j = 0; j < num_cases; j++)
  {
     cases[j] = malloc(100 * sizeof(char));
     out[j] = malloc(100 * sizeof(char));
     
  }
  
   parse(num_cases, in, cases);

   compute_output(num_cases, cases, out);

   

  
   
  for (j = 0; j < num_cases; j++)
  {
    
    if (num_operands(cases[j]) != 1) 
    {
      tmp = get_operand(cases[j], 0);
      tmp1 = get_operand(cases[j], 1);
      process_value(tmp, in_base, &val);
      process_value(tmp1, in_base, &val1);
      if (val && val1)
	printf("%s", cases[j]);
      else if (val)
      {
	cases[j] += strlen(cases[j]) - 2;
	printf("%s%c%s", tmp, ',', cases[j]);
      }
      else if (val1)
      {
	cases[j]++;
	printf("%s", cases[j]);
      }
      else
      {
	cases[j] += strlen(cases[j]) - 2;
	printf("%c%s", ',', cases[j]);
      }
    }
    else
    {
      if (*cases[j] == '0') {*cases[j] = '\0'; printf("%c", '=');}
      printf("%s", cases[j]);
    }
    printf("%s\n", out[j]);
  
    cases[j] = "\0";
    out[j] = "\0";
  }
  
  }
  
}
