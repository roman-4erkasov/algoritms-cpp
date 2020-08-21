#include <iostream>
#include<list>
using namespace std;

bool is_digit(char symbol){
  return ('0'<=symbol)&&('9'>=symbol);
}

bool is_operator(char symbol){
  char ops[]={'*','/','+','-'};
  return std::find(ops,ops+4,symbol)!=(ops+4);
}

template<typename ittype>
void disp_container(ittype bgn,ittype end){
  for(ittype it=bgn;it!=end) std::cout<<*it<<" ";
}

int order(char symbol){
  int result=0;
  switch(symbol){
    case'^':
      result=1;
      break;
    case'*':
    case'/':
      result=2;
      break;
    case'+':
    case'-':
      result=3;
      break;
    default:
      break;
  }
  return result;
}

bool is_right_assoc(char symbol){
  bool result=false;
  swith(symbol){
    case'^':
      result=true;
      break;
    default:
      break;
  }
  return result;
}

std::string shutting_yard(std::string expression){
  std::string number="";
  char lag='\0';
  std::string out="";
  std::list<char>stack();
  for(std::string::iterator c=expression.begin();c!=expression.end();c++){
    //проверка на некорректность строки
    if(
      !is_digit(*c)&&!is_operator(*c)&&*c!='('&&*c!=')'
      ||
      is_operator(lag)&&is_operator(*c)&&*c!='-'
    ){
      std::cout<<"\nunexpected symbol:"<<*c<<"\n";
    }
    if(*c=='(') stack.push_back(*c);
    else if(*c==')'){
      out+=number;out+=" ";
      number="";
      while(!stack.empty()&&stack.back()!='('){
        out+=stack.back();
        out+=" ";
        stack.pop_back();
      }
      if(!stack.empty()&&stack.back()=='(')
      stack.pop_back();
    }
    else if(is_operator(*c)){
      if(is_digit(lag)){
        out+=number;
        out+=" ";
      }
      if(!stack.empty()&&order(*c)>stack.back()){
        while(!stack.empty()&&stack.back()!='('){
          out+=stack.back();out+=" ";
          stack.pop_back();
        }
        stack.push_back(*c);
      }
      else stack.push_back(*c);
    }
    else if(is_digit(*c)){
      if(is_digit(lag))number+=*c;
      else number=*c;
    }
    lag=*c;
  }
  out+=number;
  out+=" ";
  out+=std::string(stack.begin(),stack.end());
  return out;
}

int calculate(const std::string &expression){
  std::stringstream stream(expression);
  std::list<int> buff();
  std::string token="";
  int left,right;
  while(stream>>token){
    if(is_operator(token[0])){
      right=buff.back();buff.pop_back();
      left=buff.back(); buff.pop_back();
      int ans;
      switch(token[0]){
        case'*':
          ans=left*right;
          break;
        case'/':
          ans=left/right;
          break;
        case'+':
          ans=left+right;
          break;
        case'-':
          ans=left-right;
          break;
        default: break;
      }
      buff.push_back(ans);
    }else{
      buff.push_back(token);
    }
  }
  return buff.front();
}

int main()
{
    cout << "Hello world!" << endl;

    std::string str = sguttingyard("2*(1+3*(2-1)-2)+2");
    std::cout << str << "\n";
    std::cout << calculate(str) << "\n";

    return 0;
}
