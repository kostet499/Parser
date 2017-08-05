#ifndef STRINGPARSE_H_INCLUDED
#define STRINGPARSE_H_INCLUDED

#include <iostream>
#include <cstring>
#include <vector>
#include <utility>

using namespace std;

class stringParse{

public:
    string *html;


    stringParse(string *html){
    this->html = html;
    }



    // ���� ������ ������ �� �������� � ���������� ������ long long int, � ������� ��������
    // ������� ��������� ������ ������ �� ������, ��4 �������� ���
    vector <long long int> doKmp(string a)
    {
// ������� ��� ������ ��� ��������� ���
string s = a + "@" + *html;

long long int *m, l = s.length(), p = a.length();
 vector <long long int> srtPositions;
m = new long long int [l];
for(long long int i=0; i<=p; i++) m[i]=0;

for(long long int i = p+1; i < l ; i++){
long long int j = m[i-1];
while(j>0 && s[i]!=s[j]) j  = m[j];
if(s[i]==s[j]) j++;
m[i]=j;
if(j==p) srtPositions.push_back(i-2*p);


}
delete m;
return srtPositions;
}




// search for tags with specified attribute - ���������� ������ ���������
// � �������� ������� �����, ���������� �������
//( �������� ������� - ��� ������� �����������
// ������ '>', � �� ������� ������������ ���� "</tag>"
// ����� �������� ���� ����� ����������� � ����������� �����
// ������������ �������: getTagBody, getSpcBody

// ������ �������� ��������� ����������� �������� �� � ������ ���������,
// � � ��������� �������

vector <pair <long long int, long long int> > srhSpcTag(string tag, string attr, long long int srtPos)
    {
// ������� ��� ������ ��� ��������� ���

vector <pair <long long int, long long int> > positions;

if(!(html -> length()))
{
cout<<"Sorry, empty string, function terminates";
return positions;
}


string s = "<" + tag + "@";

char *c = &((*html)[srtPos]);

long long int *m, d = s.length(), l = html -> length() - srtPos + d, p = d-1;



    string tAttr, tValue;

    int pos=0, g = attr.length();

    for(int i=0; i<g; i++)
    {
    if(attr[i]=='='){
                    pos=i+1;
                    break;
                    }
    else tAttr+=attr[i];
    }
    for(int i=pos; i<g; i++) tValue +=attr[i];

m = new long long int [l];
for(long long int i=0; i<d; i++) m[i]=0;

for(long long int i = d; i < l ; i++){

char k = c[i-d];
s += k;

long long int j = m[i-1];
while(j>0 && k!=s[j]) j  = m[j];
if(k==s[j]) j++;
m[i]=j;

    if(j==p)
    {
    long long int begPos =srtPos + i - 2*p, endPos = getTagEnd(begPos);

    string fValue = attrSearch(tAttr,begPos,endPos);

    long long int flag = srhAttrPos(&tValue,&fValue);

    if(flag != -1) positions.push_back( make_pair(begPos,endPos) );

    }


}
delete m;
return positions;
}


vector <pair <long long int, long long int> > srhSpcTag(string tag, string attr)
{
return srhSpcTag(tag, attr, 0);
}





    // ���������� ������ ��������� ���������(������ !), ��� ���� ���������������, ��������
    // ����� ���� '>' � �������� ������
    long long int srhAttrPos(string *a, long long int begPos, long long int endPos){
    string s = *a + "@";

    char *c = &((*html)[begPos]);

    long long int *m,
    p = a -> length(),
    d = p+1,
    l = endPos - begPos + d;


    long long int srtPosition = -1;
    m = new long long int [l];

    for(long long int i=0; i<d; i++) m[i]=0;

    for(long long int i = d; i < l ; i++){

    char k = c[i-d];
    s+=k;

    if(k=='>') break;
    long long int j = m[i-1];
    while(j>0 && k!=s[j]) j  = m[j];
    if(k==s[j]) j++;
    m[i]=j;
    if(j==p){
            srtPosition = begPos + i-2*p;
            break;
            }
    }
    delete m;
    return srtPosition;
    }

    // ���������� ������ ��������� ���������(������ !), ��� ���� ���������������, ��������
    // ����� ���� '>' � ������, �� ������� ��������� ��������-��������� �� ������ 'b'

    long long int srhAttrPos(string *a, string *b){

        string s = *a + "@" + *b;

        long long int *m, l = s.length(), p = a -> length();
        long long int srtPosition = -1;
        m = new long long int [l];
        for(long long int i=0; i<p+1; i++) m[i]=0;

        for(long long int i = p+1; i < l ; i++){
            if(s[i]=='>') break;
            long long int j = m[i-1];
            while(j>0 && s[i]!=s[j]) j  = m[j];
            if(s[i]==s[j]) j++;
            m[i]=j;
            if(j==p){
                srtPosition = i-2*p;
                break;
            }
        }
        delete m;
        return srtPosition;



    }





    // ����  ����� ����, ����� ��������  ���� ���� ���� � ������ � ���������� ���
    // �������� 1 - ������� ��������� ������ ���� � �������� ������
    // �������� 2 - ��� ��� ��� �������(!)
    string getTagBody(long long int tagPos, string tag)
    {
    string tagStr;
    string endTag = "</" + tag;
    string srtTag = "<" + tag;
    long long int b = html -> length(),
    c = endTag.length(),
    d = srtTag.length(),
    tagEndPos = b,
    depth = 0;
    ;
    int fl, ag;
    for(long long int i = tagPos;; i++){
    int fl = 1;
        for(int j = 0; j<c; j++)
        if((*html)[i+j]!=endTag[j])
            {
                 fl = 0;
                 break;
            }
    if(fl) depth--;
    if(fl && !depth)
        {
        tagEndPos = i;

        break;
        }
    else
        {
        int ag = 1;
        for(int j = 0; j<d; j++)
        if((*html)[i+j]!=srtTag[j])
            {
                 ag = 0;
                 break;
            }
        if(ag) depth++;

        }
    }
    depth = 0;
    long long int srtTagEnd = tagPos;
    for(;;srtTagEnd++)
    {
    char sym = (*html)[srtTagEnd];
    if(sym=='<') depth++;
    else if(sym=='>') depth--;

    if(!depth) break;
    }

    for(long long int i = srtTagEnd+1; i<tagEndPos; i++) tagStr+=(*html)[i];
    return tagStr;
    }


    long long int getTagEnd(long long int tagPos)
    {

    char *c = &((*html)[tagPos]);

    long long int depth = 0;
    long long int i;

    for(i=0;;i++){

    if(c[i]=='<') depth++;
    else if(c[i]=='>') depth--;



    if(!depth) return i+tagPos;
    }




    }
    // ���� ��������
    string attrSearch(string attr, long long int begPos, long long int endPos){

    long long int srtPos = srhAttrPos(&attr,begPos,endPos);

    if(srtPos==-1) return "";

    string attrVal;
    long long int k = srtPos + attr.length()+2;
    char *c  = &((*html)[k]);
    for(long long  i = 0;;i++)
    {
    if(c[i]=='\"')  break;
    attrVal+=c[i];
    }

    return attrVal;
    }

    // ���� ���������� �� ����������� ���� � ��������� ������ �����
    // ����� ��������� �� ����, ���������� �������.

    void getSpcBody(string tag, string attr, vector<string> *ftr, long long int srtPos){

    vector < pair< long long int, long long int> >
    t = srhSpcTag(tag,attr,srtPos);

    for(int i=0; i<t.size(); i++)
    ftr -> push_back(getTagBody(t[i].first,tag));

    }


    void getSpcBody(string tag, string attr, vector<string> *ftr)
    {
    getSpcBody(tag,attr,ftr,0);
    }




    virtual ~stringParse(){
    //destructor
    //cout<<"dest string ";
    }
};
#endif // STRINGPARSE_H_INCLUDED


