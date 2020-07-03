#pragma once
#include<vector>
#include<string>
#include<iostream>
using namespace std;

string getInputId();
string getInputPassword();
int studentLogin(const vector<string>& studentIds, const vector<string>& passwords);
bool adminLogin();
int login(const vector<string>& studentIds, const vector<string>& passwords);