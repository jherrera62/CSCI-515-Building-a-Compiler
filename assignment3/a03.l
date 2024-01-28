%option noyywrap
%{
#include<iostream>
enum{ T_DEFINITIVE_ARTICLE=1, T_ADJECTIVE, T_NOUN,T_VERB, T_PREPOSITION, T_PERIOD, T_PRONOUN, T_INTEGER };
using std::cout;
%}
%%
the|The { return T_DEFINITIVE_ARTICLE; }
quick|brown|lazy { return T_ADJECTIVE; }
fox|dog|wall|liquid|bottles { return T_NOUN; }
jumped|see { return T_VERB; }
over|on|of { return T_PREPOSITION; }
\. { return T_PERIOD; }
I { return T_PRONOUN; }
[0-9]+ { return T_INTEGER; }
%%
int main()
{
 int yyl=-1;
 while(yyl)
 {
  yyl=yylex();
  switch(yyl)
  {
    case 1:
        cout<<"T_DEFINITIVE_ARTICLE";
        break;
    case 2:
        cout<<"T_ADJECTIVE";
        break;
    case 3:
        cout<<"T_NOUN";
        break;
    case 4:
        cout<<"T_VERB";
        break;
    case 5:
        cout<<"T_PREPOSITION";
        break;
    case 6:
        cout<<"T_PERIOD";
        break;
    case 7:
        cout<<"T_PRONOUN";
        break;
    case 8:
        cout<<"T_INTEGER";
        break;
    default:
        break;
  }
 }

 return 0;
}
