#ifndef __ENV_HPP__
#define __ENV_HPP__

#include <string>
#include <iostream>
#include <map>
#include "expression.hpp"

using namespace std;

/**********************************************************/
/**/
/**********************************************************/
class env
{
private:
    map<string, expr*> m_env;
public:
    env();
    env(string name, expr* expression);
    ~env();

    void set(string name, expr* expression);
    expr* get(string name);
    void print();
};

env::env()
{

}

env::env(string name, expr* expression)
{
    m_env[name] = expression;
}

env::~env()
{
}

void env::set(string name, expr* expression)
{
    m_env[name] = expression;
}

expr* env::get(string name)
{
    if (m_env[name] == NULL)
    {
        /* 临时处理 */
        return m_env[name] = new num(0);
    }
    else
    {
        return m_env[name];
    }
}

void env::print()
{
    map<string, expr*> :: iterator it ;

    cout << "{";
    for(it = m_env.begin() ; it != m_env.end() ; it++)
    {
        cout << "(" ;
        cout << it->first << "=";
        ((expr*)it->second)->to_s();
        cout << ")" ;
    }
    cout << "}";
}

#endif