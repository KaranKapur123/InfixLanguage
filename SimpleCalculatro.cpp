#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;
class Token{
    string TokenType;
    string Value;
    public:
    Token(){
    }
    Token(string tokentype,char value){
        TokenType=tokentype;
        Value=value;
    }
    Token(string tokentype,string value){
        TokenType=tokentype;
        Value=value;
    }
    Token(string tokentype){
        TokenType=tokentype;
    }
    string getValue(){                   //GETTER FOR VALUE   
        return Value;
    }
    string getTokenType(){
        return TokenType;
    }
    string tokenToString(){           //CONVERTS TOKEN CLASS TO A STRING THAT CAN BE USED FOR OUTPUT
        string result;
    result+="[";
    result+=TokenType;
    result+=", ";
    result+=Value;
    result+="]";
    return result;
    }
    void eat(string tokentype1){    //CHECKS IF TOKEN IS OF THE RIGHT TYPE
        if(TokenType!=tokentype1) throw invalid_argument("Invalid Input");
    }
    void eat(string tokentype1,string tokentype2){    //CHECKS IF TOKEN IS OF THE RIGHT TYPE
        if(TokenType==tokentype1||TokenType==tokentype2){}
        else throw invalid_argument("Invalid Input");
    }
    void eat(string tokentype1,string tokentype2,string tokentype3){    //CHECKS IF TOKEN IS OF THE RIGHT TYPE
        if(TokenType==tokentype1||TokenType==tokentype2||TokenType==tokentype3){}
        else throw invalid_argument("Invalid Input");
    }

};
class Interpreter{
    int Position=0;
    string Input;
    Token CurrentToken;
    public:
    Interpreter(string input){      
        Input=input;
        removeWhiteSpace();
    }
    Token getNextToken(){                   //GETS NEXT TOKEN IN THE INPUT STRING
        if (Position<Input.length()){
            if (isdigit(Input[Position])){
                string tokenvalue;
                while(Position<Input.length()&&isdigit(Input[Position])){
                    tokenvalue.push_back(Input[Position]);
                    Position++;
                }
                    CurrentToken=Token("Integer",tokenvalue);
                    return(Token("Integer",tokenvalue));
                }
            if(Input[Position]=='+'||Input[Position]=='-'||Input[Position]=='*'||Input[Position]=='/'){
                    Position++;
                    CurrentToken=Token("Operator",Input[Position-1]);
                    return(Token("Operator",Input[Position-1]));
                }
            if(Input[Position]=='(') {
                    Position++;
                    CurrentToken=Token("LParen",Input[Position-1]);
                    return(Token("LParen",Input[Position-1]));
            }
            if(Input[Position]==')') {
                    Position++;
                    CurrentToken=Token("RParen",Input[Position-1]);
                    return(Token("RParen",Input[Position-1]));
            }
            throw invalid_argument("Invalid Input");
        }else{
            CurrentToken=Token("EOL");
            return(Token("EOL"));
        }    
    }
    int stringToInteger(string str){                //CONVERTS STRING TO INTEGER
        int result=0;
        for(int i=0;i<str.length();i++){
            if(!isdigit(str[i])){
                throw invalid_argument("Invalid Input");
            }
            result *=10;
            result+=(int(str[i])-int('0'));
        }
        return result;
    }
    void removeWhiteSpace(){                //REMOVES WHITESPACES FROM INPUT
        string result;
        for(int i=0;i<Input.length();i++){
            if(Input[i]!=' '){
                result.push_back(Input[i]);
            }
        }
        Input=result;
    }
    void advance(){                         //INCREMENT POSITION
        Position++;
    }
    void back(){                            //DECREMENT POSITION
        Position--;
    }
    int term(){
        int result=factor();
        Token op=getNextToken();
        while(op.getValue()[0]=='*'||op.getValue()[0]=='/'){
            int right=factor();
            if (op.getValue()[0]=='*'){
                result *= right;
            }else if (op.getValue()[0]=='/'){
                result /= right;
            }
            op=getNextToken();
        }
        back();
        return result;
    }
    int factor(){
        Token factor=getNextToken();
        factor.eat("Integer","LParen");
        if(factor.getTokenType()=="Integer"){
            int result=stringToInteger(factor.getValue());
            return result;
        }else if(factor.getTokenType()=="LParen"){
            int result=expr();
            Token RightPara=getNextToken();
            RightPara.eat("RParen");        
            return result;
        }
    }
    int expr(){
        int result=term();
        Token op=getNextToken();
        while(op.getValue()[0]=='+'||op.getValue()[0]=='-'){
            int right=term();
            if (op.getValue()[0]=='+'){
                result += right;
            }else if (op.getValue()[0]=='-'){
                result -= right;
            }
            op=getNextToken();
        }
        back();
        return result;
    }
     
    // int evaluate(){                         //MAIN CLASS OF INTERPRETER
    //     int result;
    //     Token left=getNextToken();
    //     result=stringToInteger(left.getValue());
    //     Token op=getNextToken();
    //     op.eat("Operator","EOL");
    //     while(op.getTokenType()=="Operator"){
    //         Token right=getNextToken();
    //         right.eat("Integer");
    //         switch(op.getValue()[0]){
    //             case '+':
    //             result += stringToInteger(right.getValue());
    //             break;
    //             case '-':
    //             result -= stringToInteger(right.getValue());
    //             break;
    //             case '*':
    //             result *= stringToInteger(right.getValue());
    //             break;
    //             case '/':
    //             result /= stringToInteger(right.getValue());
    //             break;
    //             default:
    //             throw invalid_argument("Invalid Input");
    //         }
    //         op=getNextToken();
    //         op.eat("Operator","EOL");
    //     }
    //     return result;
    // }
};
int main(){
    bool a=true;
    while (a){
        string input;
        cout << ">> ";
        getline(cin,input);
        Interpreter inp(input);
        cout << inp.expr() << endl;
    }
    return 0;
};