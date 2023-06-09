#include <iostream>
#include <vector>
using namespace std;
class BankAccount
{
public:
	friend class TimeDepositAccount;
	BankAccount(string name, string account_no, int level, double money);
	string get_name();
	void set_name(string name);
	string get_account_no();
	void set_account_no(string account_no);
	double get_balance();
	void set_balance(double balance);
	int get_level();
	void set_level(int level);
	virtual void withdraw(double money);
	virtual void deposit(double money);
	static double get_all_money();
private:
	string name_;
	string account_no_;
	double balance_;
	int level_;
	static double all_money_;
};
class TimeDepositAccount :public BankAccount
{
public:
	TimeDepositAccount(string name, string account_no, int level, int time, double money);
	void withdraw(double money);
	void deposit(double money);
private:
	int time_;
};
double BankAccount::all_money_ = 0;
double BankAccount::get_all_money()
{
	return all_money_;
}
BankAccount::BankAccount(string name, string account_no, int level, double money) :name_(name), account_no_(account_no), level_(level), balance_(money)
{
	cout << "开户成功! 姓名: " << name << " 账户号: " << account_no << " 账户等级: " << level << " 余额: " << money << endl;
	all_money_ += money;
}
string BankAccount::get_name()
{
	return name_;
}
void BankAccount::set_name(string name)
{
	name_ = name;
}
string BankAccount::get_account_no() {
	return account_no_;
}
void BankAccount::set_account_no(string account_no)
{
	account_no_ = account_no;
}
double BankAccount::get_balance()
{
	return balance_;
}
void BankAccount::set_balance(double balance)
{
	balance_ = balance;
}
int BankAccount::get_level()
{
	return level_;
}
void BankAccount::set_level(int level)
{
	level_ = level;
}
void BankAccount::withdraw(double money)
{
	if (balance_ < money)
	{
		cout << "余额不足,当前余额: "<< balance_ << endl;
	}
	else
	{
		balance_ -= money;
		all_money_ -= money;
		cout << "取款成功,剩余余额: " << balance_ << endl;
	}
}
void BankAccount::deposit(double money)
{
	balance_ += money;
	all_money_ += money;
	cout << "存款成功,当前余额为: "<< balance_ << endl;
}
TimeDepositAccount::TimeDepositAccount(string name, string account_no, int level, int time, double money) :BankAccount(name, account_no, level,money), time_(time)
{
	;
}
void TimeDepositAccount::withdraw(double money)
{
	if (time_ > 0)
	{
		cout << "未到期限,无法存取款!" << endl;
	}
	else
	{
		if (balance_ < money)
		{
			cout << "余额不足,当前余额: " << balance_ << endl;
		}
		else
		{
			balance_ -= money;
			
			cout << "取款成功,剩余余额: " << balance_ << endl;
		}
	}
}
void TimeDepositAccount::deposit(double money)
{
	if (time_ > 0)
	{
		cout << "未到期限,无法存取款!" << endl;
	}
	else
	{
		balance_ += money;
		cout << "存款成功,当前余额为: " << balance_ << endl;
	}
}
char menu()
{
	cout << "-------菜单--------" << endl;
	cout << "*    1.开户       *" << endl;
	cout << "*    2.操作       *" << endl;
	cout << "*    3.退出       *" << endl;
	char select;
	cin >> select;
	return select;
}
void menu2()
{
	cout << "-------菜单--------" << endl;
	cout << "*    1.存款       *" << endl;
	cout << "*    2.取款       *" << endl;
	cout << "*    3.查询       *" << endl;
}
int main()
{
	vector<BankAccount*> bank;
	while (true)
	{
		char select = menu();
		if (select == '1')
		{
			cout << "输入姓名: ";
			string name;
			cin >> name;
			cout << "输入账户号: ";
			string no;
			cin >> no;
			cout << "输入等级: ";
			int level;
			cin >> level;
			cout << "输入初始存款量: ";
			double money;
			cin >> money;
			while (true)
			{
				cout << "是否是定期存款账户(y/n): ";
				char yorn;
				cin >> yorn;
				if (yorn == 'y' || yorn == 'Y') {
					cout << "输入时间年限:";
					int time;
					cin >> time;
					bank.push_back(new TimeDepositAccount(name, no, level, time, money));
					break;
				}
				else if (yorn == 'n' || yorn == 'N') {
					bank.push_back(new BankAccount(name, no, level, money));
					break;
				}
				else {
					continue;
				}
			}
		}
		else if (select == '2')
		{
			cout << "一共有" << bank.size() << "个银行账户\n" << endl;
			for (int i = 0; i < bank.size(); ++i)
			{
				cout << i + 1 << ". 姓名: " << bank[i]->get_name() << " 账号: "<< bank[i]->get_account_no() << endl;
			}
			cout << "\n银行一共存了" << BankAccount::get_all_money() << "元" << endl;
			int sc;
			while (1)
			{
				cout << "操作哪个账户(输入序号): ";
				cin >> sc;
				if (--sc < bank.size()) {
					while (true)
					{
						menu2();
						char c;
						cin >> c;
						if (c == '1')
						{
							cout << "需要存多少: ";
							double m;
							cin >> m;
							bank[sc]->deposit(m);
							break;
						}
						else if (c == '2')
						{
							cout << "需要取多少: ";
							double m;
							cin >> m;
							bank[sc]->withdraw(m);
							break;
						}
						else if (c == '3')
						{
							cout << bank[sc]->get_name() << "的存款为: " << bank[sc]->get_balance() << endl;
							break;
						}
						else { continue; }
					}
					break;
				}
				else {
					continue;
				}
			}
		}
		else if (select == '3')
		{
			break;
		}
		else {
			continue;
		}
	}

	return 0;
}