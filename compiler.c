#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
FILE *p1,*p2,*p3,*p4,*p5,*p6,*p7,*p8,*p9,*p10;
char c,c1;
int symbCnt=0,size=0;

struct SymbTab
{
    char name[10],id_type[10],data_type[10],scope[10],value[15];
    int sl;
    struct SymbTab *next;
};

struct SymbTab *first,*last;

void removeCommentNewline()
{
    p1=fopen("input.c","r");
    p2=fopen("comment_newline_removed.txt","w");

    if(!p1)
    {
        printf("File can't be opened!");
    }
    else
    {
        c1=fgetc(p1);
        while(c1!=EOF)
        {
            c=c1;
            c1=fgetc(p1);

            if((c=='/')&&(c1=='*'))
            {
                c1=fgetc(p1);
                while((c!='*')&&(c1!='/'))
                {
                    c=c1;
                    c1=fgetc(p1);
                }
                c=fgetc(p1);
                c1=fgetc(p1);
            }
            else if((c=='/')&&(c1=='/'))
            {
                c1=fgetc(p1);
                while(!(c1=='\n'))
                {
                    c1=fgetc(p1);
                }
                c=fgetc(p1);
                c1=fgetc(p1);
            }
            else if(c=='#')
            {
                while(!(c1=='\n'))
                {
                    c1=fgetc(p1);
                }
                c=fgetc(p1);
                c1=fgetc(p1);
            }

            if(c!='\n')
                fputc(c,p2);
            else
                fputc(' ',p2);
        }
    }

    fclose(p1);
    fclose(p2);

    p2=fopen("comment_newline_removed.txt","r");

    printf("Comment and newline removed output:\n");
    while((c=fgetc(p2))!=EOF)
    {
        printf("%c",c);

    }
    printf("\n");

    fclose(p2);
}

void removeExtraSpace()
{
    int p=0,i=0;
    char printf_checker[] = "printf";
    char str[10];

    p2=fopen("comment_newline_removed.txt","r");
    p3=fopen("extra_space_removed.txt","w");

    while((c=fgetc(p2))!=EOF)
    {
        if (c=='p')
        {
            p=1;
            i=0;
            fputc(c,p3);
        }
        else if(c==' '||c=='\t')
        {
            while(c==' '||c=='\t')
            {
                c=fgetc(p2);
            }
            fputc(' ',p3);
            fputc(c,p3);
            if(c=='p')
            {
                p=1;
                i=0;
            }
        }
        else
        {
            fputc(c,p3);
        }

        if(p==1)
        {
            str[i]=c;
            i++;
            if(i==6)
            {
                str[i]='\0';
                i=0;
                if(strcmp(printf_checker,str)==0)
                    p=2;

            }
        }

        if(p==2 && c=='"')
        {
            c=fgetc(p2);
            while(c!='"')
            {
                fputc(c,p3);
                c=fgetc(p2);
            }
            fputc(c,p3);
            p=0;
            i=0;
        }
    }

    fclose(p2);
    fclose(p3);

    p3=fopen("extra_space_removed.txt","r");

    printf("\nExtra space removed output:\n");
    while((c=fgetc(p3))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    fclose(p3);
}

void seperateLexims()
{
    int l=0, k=0, m=0;
    char paran[]="(){}[]";
    char sep[]=";,':";
    char one_charc_op[]="+-*/%><!&|^~=";

    p3=fopen("extra_space_removed.txt","r");
    p4=fopen("lexims.txt","w");

    while((c=fgetc(p3))!=EOF)
    {
        while(c!=' ')
        {
            c1=c;
            c=fgetc(p3);

            if(c==EOF)
            {
                c=c1;
                break;
            }

            for(int i=0; i<6; i++)
            {
                if(c1==paran[i])
                {
                    if(c!=' ')
                        l=1;
                }
            }
            for(int i=0; i<6; i++)
            {
                if(c==paran[i])
                {
                    if(c1!=' ')
                        l=1;
                }
            }
            for(int i=0; i<4; i++)
            {
                if(c1==sep[i])
                {
                    if(c!=' ')
                        l=1;
                }
            }
            for(int i=0; i<4; i++)
            {
                if(c==sep[i])
                {
                    if(c1!=' ')
                        l=1;
                }
            }
            for(int i=0; i<13; i++)
            {
                if(c1==one_charc_op[i])
                {
                    if(c!=' ')
                    {
                        for(int j=0; j<13; j++)
                        {
                            if(c==one_charc_op[j])
                            {
                                k=1;
                            }
                        }
                        if(k==0)
                        {
                            l=1;
                        }
                        else
                        {
                            l=0;
                            k=0;
                            m=1;
                        }
                    }
                }
            }
            if(m==0)
            {
                for(int i=0; i<13; i++)
                {
                    if(c==one_charc_op[i])
                    {
                        if(c1!=' ')
                            l=1;
                    }
                }
            }
            if(l==1)
            {
                fputc(c1,p4);
                fputc(' ',p4);
                l=0;
            }
            else
            {
                fputc(c1,p4);
                m=0;
            }
        }
        fputc(c,p4);
    }
    fclose(p3);
    fclose(p4);

    p4=fopen("lexims.txt","r");

    printf("\nLexims:\n");
    while((c=fgetc(p4))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    fclose(p4);
}


bool paran_rec(char *lex)
{
    char paran[10][10]= {"(",")","{","}","[","]"};
    for(int i=0; i<6; i++)
    {
        if(strcmp(paran[i],lex)==0)
            return true;
    }
    return false;
}

bool sep_rec(char *lex)
{
    char sep[10][10]= {";",",","'",":"};
    for(int i=0; i<4; i++)
    {
        if(strcmp(sep[i],lex)==0)
            return true;
    }
    return false;
}

bool op_rec(char *lex)
{
    char op[40][40]= {"+","-","*","/","%",">","<","!","&","|","^","~","=",
                      "++","--","==","!=",">=","<=","&&","||","<<",">>",
                      "+=","-=","*=","/=","%=","&=","|=","^=","<<=",">>="
                     };
    for(int i=0; i<33; i++)
    {
        if(strcmp(op[i],lex)==0)
            return true;
    }
    return false;
}

bool kw_rec(char *lex)
{
    char keywords[40][40] = {"switch","typedef","union",
                             "unsigned","void","long","register","short","signed",
                             "sizeof","static","volatile","while","auto","break","case","char","const","continue","default",
                             "do","double","enum","extern","return","struct","float","for","goto",
                             "if","int","else"
                            };

    for(int i = 0; i < 32; i++)
    {
        if(strcmp(keywords[i], lex) == 0)
        {
            return true;
        }
    }
    return false;
}

bool num_rec(char *lex)
{
    int i, l, s;
    i=0;
    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else
        s=0;

    l=strlen(lex);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==2)
    {
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
            s=0;
    }
    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
                s=3;
            else
            {
                s=0;
                break;
            }
        }
    }
    if(s==3)
        s=1;

    if(s==1)
        return true;
    else
        return false;
}

bool ident_rec(char *lex)
{
    char symbol[]="/*-+`~!@#$%^&()={}[]\|;:'<>,?";
    if (isdigit(lex[0]))
    {
        return false;
    }
    else
    {
        for(int i=0; i<29; i++)
        {
            if(symbol[i]==lex[0])
                return false;
        }
    }

    int len = strlen(lex);
    if (len == 1)
    {
        return true;
    }
    else
    {
        for (int i = 1 ; i < len ; i++)
        {
            for(int j=0; j<29; j++)
            {
                if(symbol[j]==lex[i])
                    return false;
            }
        }
        return true;
    }
}

void tokenize()
{
    char str[15],ch[15];
    int i=0,j=0;

    p4=fopen("lexims.txt","r");
    p5=fopen("tokens.txt","w");
    p6=fopen("id_tokens.txt","w");

    while((c=fgetc(p4))!=EOF)
    {
        while(c!=' ')
        {
            str[i]=c;
            i++;
            c=fgetc(p4);
            if(c==EOF)
                break;
        }
        str[i]='\0';
        i=0;
        if(paran_rec(str))
        {
            strcpy(ch,"par");
        }
        else if(sep_rec(str))
        {
            strcpy(ch,"sep");
        }
        else if(op_rec(str))
        {
            strcpy(ch,"op");
        }
        else if(num_rec(str))
        {
            strcpy(ch,"num");
        }
        else if(kw_rec(str))
        {
            strcpy(ch,"kw");
        }
        else if(ident_rec(str))
        {
            strcpy(ch,"id");
            j=1;
        }
        else
        {
            strcpy(ch,"unkn");
        }

        fputc('[',p5);
        fputs(ch,p5);
        fputc(' ',p5);
        fputs(str,p5);
        fputc(']',p5);

        if(j==1)
        {
            fputc('[',p6);
            fputs(ch,p6);
            fputc(' ',p6);
            fputs(str,p6);
            fputc(']',p6);
            j=0;
        }
        else
        {
            fputc('[',p6);
            fputs(str,p6);
            fputc(']',p6);
        }
    }

    fclose(p4);
    fclose(p5);
    fclose(p6);

    p5=fopen("tokens.txt","r");

    printf("\nTokens:\n");
    while((c=fgetc(p5))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    fclose(p5);

    p6=fopen("id_tokens.txt","r");

    printf("\nid_tokens:\n");
    while((c=fgetc(p6))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    fclose(p6);
}

void Insert(char *n,char *i,char *d,char *s,char *v)
{
    int m;
    m=Search(n,s);

    if(m==0)
    {
        struct SymbTab *p;
        p=malloc(sizeof(struct SymbTab));
        strcpy(p->name,n);
        strcpy(p->id_type,i);
        strcpy(p->data_type,d);
        strcpy(p->scope,s);
        strcpy(p->value,v);
        //p->value=v;
        p->sl=++symbCnt;
        p->next=NULL;

        if(size==0)
        {
            first=p;
            last=p;
        }
        else
        {
            last->next=p;
            last=p;
        }
        size++;
    }
}

void Display()
{
    int i;
    struct SymbTab *p;
    p=first;
    printf("\nSymbol Table:\n");
    printf("\n\tSl.No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    for(i=0; i<size; i++)
    {
        printf("\t%d\t\t%s\t\t%s\t\t%s\t\t%s\t\t%s\n",p->sl,p->name,p->id_type,p->data_type,p->scope,p->value);
        p=p->next;
    }
}

int Search(char *n,char *s)
{
    int i,flag=0;
    struct SymbTab *p;
    p=first;
    for(i=0; i<size; i++)
    {
        if(strcmp(p->name,n)==0 && strcmp(p->scope,s)==0)
            flag=p->sl;
        p=p->next;
    }
    return flag;
}

void Delete(char *n,char *s)
{
    int a;
    struct SymbTab *p,*q;
    p=first;
    a=Search(n,s);
    if(a!=0)
    {
        if(strcmp(first->name,n)==0 && strcmp(first->scope,s)==0)
            first=first->next;
        else if(strcmp(last->name,n)==0 && strcmp(last->scope,s)==0)
        {
            q=p->next;
            while(strcmp(q->name,n)!=0 && strcmp(q->scope,s)!=0)
            {
                p=p->next;
                q=q->next;
            }
            p->next=NULL;
            last=p;
        }
        else
        {
            q=p->next;
            while(strcmp(q->name,n)!=0 && strcmp(q->scope,s)!=0)
            {
                p=p->next;
                q=q->next;
            }
            p->next=q->next;
        }
        size--;
    }
}

void Update(char *n,char *s,char *v)
{
    int i,b;
    struct SymbTab *p;
    p=first;
    b=Search(n,s);
    if(b!=0)
    {
        for(i=0; i<size; i++)
        {
            if(strcmp(p->name,n)==0 && strcmp(p->scope,s)==0)
                strcpy(p->value,v);
            p=p->next;
        }
    }
}

void generateSymbolTable()
{
    char str1[15], str2[15], str3[10], id[]="id ", name[10], id_type[10], scope[]="global";
    char dtypes[10][10] = {"int","float","double","char","void"};
    int i,r,flag;
    p6=fopen("id_tokens.txt","r");

    while((c=fgetc(p6))!=EOF)
    {
        i=0;
        r=0;
        while((c=fgetc(p6))!=']')
        {
            if(c=='}' && flag==1)
            {
                strcpy(scope,"global");
                scope[6]='\0';
                flag=0;
            }
            str1[i]=c;
            i++;
        }
        str1[i]='\0';
        i=0;

        for(int j=0; j<5; j++)
        {
            if(strcmp(dtypes[j],str1)==0)
                r=1;
        }

        if(r==1)
        {
            c=fgetc(p6);
            while((c=fgetc(p6))!=']')
            {
                if(c=='}' && flag==1)
                {
                    strcpy(scope,"global");
                    scope[6]='\0';
                    flag=0;
                }
                str2[i]=c;
                i++;
            }
            str2[i]='\0';

            if(strlen(str2)>3)
            {
                strncpy(str3,str2,3);
                str3[3]='\0';

                if(strcmp(str3,id)==0)
                {
                    strncpy(name,str2+3,strlen(str2)-3);
                    name[strlen(str2)-3]='\0';

                    c=fgetc(p6);
                    c=fgetc(p6);
                    if(c=='(')
                    {
                        if(strcmp(scope,"global")==0)
                        {
                            Insert(name,"func",str1,scope,"Not assigned");
                            strcpy(scope,name);
                            flag=1;
                        }
                    }
                    else
                    {
                        Insert(name,"var",str1,scope,"Not assigned");
                    }
                    c=fgetc(p6);
                }
            }
        }
    }

    fclose(p6);

    p6=fopen("id_tokens.txt","r");

    flag=0;
    scope[7]="global";
    while((c=fgetc(p6))!=EOF)
    {
        i=0;
        while((c=fgetc(p6))!=']')
        {
            if(c=='}' && flag==1)
            {
                strcpy(scope,"global");
                scope[6]='\0';
                flag=0;
            }
            str1[i]=c;
            i++;
        }
        str1[i]='\0';
        i=0;
        if(strlen(str1)>3)
        {
            strncpy(str3,str1,3);
            str3[3]='\0';

            if(strcmp(str3,id)==0)
            {
                strncpy(name,str1+3,strlen(str1)-3);
                name[strlen(str1)-3]='\0';

                c=fgetc(p6);
                c=fgetc(p6);
                if(c=='(')
                {
                    strcpy(scope,name);
                    flag=1;
                }
                else if((c=='='))
                {
                    i=0;
                    c=fgetc(p6);
                    c=fgetc(p6);
                    while((c=fgetc(p6))!=']')
                    {
                        str2[i]=c;
                        i++;
                    }
                    str2[i]='\0';
                    i=0;

                    Update(name,scope,str2);
                }
                c=fgetc(p6);
            }
        }
    }
    fclose(p6);
    Display();

    p6=fopen("id_tokens.txt","r");
    p7=fopen("modifed_tokens.txt","w");

    flag=0;
    i=0;
    scope[7]="global";
    while((c=fgetc(p6))!=EOF)
    {
        i=0;
        fputc(c,p7);
        while((c=fgetc(p6))!=']')
        {
            if(c=='}' && flag==1)
            {
                strcpy(scope,"global");
                scope[6]='\0';
                flag=0;
            }
            str1[i]=c;
            i++;
        }
        str1[i]='\0';
        i=0;

        if(strlen(str1)>3)
        {
            strncpy(str3,str1,3);
            str3[3]='\0';

            if(strcmp(str3,id)==0)
            {
                fputs(id,p7);
                strncpy(name,str1+3,strlen(str1)-3);
                name[strlen(str1)-3]='\0';
                int x = Search(name,scope);
                char id_num[5];
                itoa(x, id_num, 10);
                fputs(id_num,p7);
                fputc(']',p7);
                c=fgetc(p6);
                fputc(c,p7);
                c=fgetc(p6);
                fputc(c,p7);

                if(c=='(')
                {
                    strcpy(scope,name);
                    flag=1;
                }
                c=fgetc(p6);
                fputc(c,p7);
            }
            else
            {
                fputs(str1,p7);
                fputc(']',p7);
            }

        }
        else
        {
            fputs(str1,p7);
            fputc(']',p7);
        }
    }
    fclose(p6);
    fclose(p7);

    p7=fopen("modifed_tokens.txt","r");

    printf("\nModified_tokens:\n");
    while((c=fgetc(p7))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    fclose(p7);

}

void assignLineNumber()
{
    int l=0, k=0, m=0, n=0;
    char paran[]="(){}[]";
    char sep[]=";,':";
    char one_charc_op[]="+-*/%><!&|^~=";
    p1=fopen("input.c","r");
    p8=fopen("line_number_assigned.txt","w");
    int i=1,j,flag=0;
    char id_num[5];
    char str[50];
    char str1[15],ch[15];
    int x=0,y=0;


    while((c=fgetc(p1))!=EOF)
    {
        j=0;
        itoa(i, id_num, 10);
        fputs(id_num,p8);
        fputc(' ',p8);

        while(c!='\n')
        {
            str[j]=c;
            c=fgetc(p1);
            j++;
        }

        str[j]='\0';

        for(int k=0; k<strlen(str); k++)
        {
            if((str[k]=='/')&&(str[k+1]=='*'))
            {
                k+=2;
                flag=1;
                while((str[k]!='*')&&(str[k+1]!='/'))
                {
                    k++;
                    flag=0;
                }
                k++;
            }
            else if(((str[k]=='/')&&(str[k+1]=='/')) || str[k]=='#')
            {
                break;
            }
            else if(str[k]==' ' || str[k]=='\t')
            {
                while(str[k]==' ' || str[k]=='\t')
                {
                    k++;
                }
                fputc(' ',p8);
                fputc(str[k],p8);
            }
            else
            {
                fputc(str[k],p8);
            }
        }
        //printf("\n%s",str);
        fputc(c,p8);
        i++;
    }

    fclose(p1);
    fclose(p8);

    p8=fopen("line_number_assigned.txt","r");
    p9=fopen("line_number_assigned2.txt","w");

    while((c=fgetc(p8))!=EOF)
    {
        while(c!=' ')
        {
            c1=c;
            c=fgetc(p8);

            if(c==EOF)
            {
                c=c1;
                break;
            }

            for(int i=0; i<6; i++)
            {
                if(c1==paran[i])
                {
                    if(c!=' ')
                        l=1;
                }
            }
            for(int i=0; i<6; i++)
            {
                if(c==paran[i])
                {
                    if(c1!=' ')
                        l=1;
                }
            }
            for(int i=0; i<4; i++)
            {
                if(c1==sep[i])
                {
                    if(c!=' ')
                        l=1;
                }
            }
            for(int i=0; i<4; i++)
            {
                if(c==sep[i])
                {
                    if(c1!=' ')
                        l=1;
                }
            }
            for(int i=0; i<13; i++)
            {
                if(c1==one_charc_op[i])
                {
                    if(c!=' ')
                    {
                        for(int j=0; j<13; j++)
                        {
                            if(c==one_charc_op[j])
                            {
                                k=1;
                            }
                        }
                        if(k==0)
                        {
                            l=1;
                        }
                        else
                        {
                            l=0;
                            k=0;
                            m=1;
                        }
                    }
                }
            }
            if(m==0)
            {
                for(int i=0; i<13; i++)
                {
                    if(c==one_charc_op[i])
                    {
                        if(c1!=' ')
                            l=1;
                    }
                }
            }
            if(l==1)
            {
                fputc(c1,p9);
                fputc(' ',p9);
                l=0;
            }
            else
            {
                fputc(c1,p9);
                m=0;
            }
        }
        fputc(c,p9);
    }
    fclose(p8);
    fclose(p9);

    p9=fopen("line_number_assigned2.txt","r");
    p10=fopen("line_number_assigned3.txt","w");

    c=fgetc(p9);
    fputc(c,p10);
    c=fgetc(p9);
    fputc(c,p10);

    while((c=fgetc(p9))!=EOF)
    {
        if(c=='\n')
        {
            fputc(c,p10);
            c=fgetc(p9);
            if(c==EOF)
                break;
            else
            {
                while(c!=' ')
                {
                    fputc(c,p10);
                    c=fgetc(p9);
                }
            }
            fputc(c,p10);
            continue;
        }
        while(c!=' ')
        {
            str1[x]=c;
            x++;
            c=fgetc(p9);
            if(c==EOF)
                break;
        }
        str1[x]='\0';
        x=0;
        if(paran_rec(str1))
        {
            strcpy(ch,"par");
        }
        else if(sep_rec(str1))
        {
            strcpy(ch,"sep");
        }
        else if(op_rec(str1))
        {
            strcpy(ch,"op");
        }
        else if(num_rec(str1))
        {
            strcpy(ch,"num");
        }
        else if(kw_rec(str1))
        {
            strcpy(ch,"kw");
        }
        else if(ident_rec(str1))
        {
            strcpy(ch,"id");
        }
        else
        {
            strcpy(ch,"unkn");
        }

        //fputc('[',p5);
        fputs(ch,p10);
        fputc(' ',p10);
        fputs(str1,p10);
        fputc(' ',p10);
    }
    fclose(p9);
    fclose(p10);

    p10=fopen("line_number_assigned3.txt","r");

    printf("\n\n");
    while((c=fgetc(p10))!=EOF)
    {
        printf("%c",c);
    }
    printf("\n");

    fclose(p10);

}

void detectErrors()
{
    int i,j=0,x,y,p=0,q=0;
    char stack[50],top;
    char line_number[10];
    char str1[15],str2[15],str3[15],str4[15];
    p10=fopen("line_number_assigned3.txt","r");

    while((c=fgetc(p10))!=EOF)
    {
        i=0,x=0,y=0;
        while(c!=' ')
        {
            line_number[i]=c;
            c=fgetc(p10);
            i++;
        }
        line_number[i]='\0';

        while((c=fgetc(p10))!='\n')
        {
            while(c!=' ')
            {
                str1[x]=c;
                x++;
                c=fgetc(p10);
            }
            str1[x]='\0';
            x=0;

            c=fgetc(p10);
            while(c!=' ')
            {
                str3[y]=c;
                y++;
                c=fgetc(p10);
            }
            str3[y]='\0';
            y=0;

            if(str3[y] == '(' || str3[y] == '{' || str3[y] == '[')
            {
                stack[p]=str3[y];
                p++;
            }
            else if(str3[y] == ')' || str3[y] == '}' || str3[y] == ']')
            {
                if(p==0)
                {
                    printf("\nMisplaced %c at %s\n",str3[y],line_number);
                }
                else
                {
                    top = stack[p-1];

                    if(str3[y] == ')' && top == '(' ||
                            str3[y] == '}' && top == '{' ||
                            str3[y] == ']' && top == '[')
                    {
                        p--;
                    }
                    else
                    {
                        printf("\nMisplaced %c at %s\n",str3[y],line_number);
                    }
                }
            }

            if(strcmp(str3,"if")==0)
            {
                j=1;
            }

            if(strcmp(str3,"else")==0)
            {
                if(j==0)
                    printf("\nUnmatched else at %s\n",line_number);
                else
                    j=0;
            }

            if(strcmp(str1,str2)==0)
            {
                if((strcmp(str4,"else"))==0 && (strcmp(str3,"if"))==0) {}
                else if((strcmp(str2,"par"))==0 && (strcmp(str1,"par"))==0) {}
                else
                    printf("\nDuplicate token at line %s\n",line_number);
            }

            strcpy(str2,str1);
            strcpy(str4,str3);
        }
        strcpy(str2,"");
        strcpy(str4,"");
        strcpy(str1,"");
        strcpy(str3,"");
    }
    if(p>0){
        printf("\nMisplaced Parenthesis\n");
    }
    fclose(p10);
}

int main()
{
    printf("Write a C program:\n");

    p1=fopen("input.c","w");

    while((c=fgetchar())!=EOF)
    {
        fputc(c,p1);
    }
    printf("\nProgram saved successfully!\n\n");

    fclose(p1);

//Assignment - 1

    removeCommentNewline();

//Assignment - 2

    removeExtraSpace();

    seperateLexims();

    tokenize();

//Assignment - 3

    generateSymbolTable();

//Assignment - 4

    assignLineNumber();

    detectErrors();

    return 0;
}
