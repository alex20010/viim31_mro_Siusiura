#include "MyForm.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace System;
using namespace System::Windows::Forms;

class circle 
{
private:
	double x0[3], y0[3], r0[3], xt[15], yt[15];

public:
	
	int getr(int a)
	{
		return r0[a];
	}
	int getx(int a)
	{
		return x0[a];
	}
	int gety(int a)
	{
		return y0[a];
	}
	int getxt(int a)
	{
		return xt[a];
	}
	int getyt(int a)
	{
		return yt[a];
	}

	void setr(int a, int b)
	{
		r0[a] = b;
	}
	void setx(int a, int b)
	{
		x0[a] = b;
	}
	void sety(int a, int b)
	{
		y0[a] = b;
	}

	void randt()
	{
		Random^ ran = gcnew Random();
		for (int u = 0; u < 3; u++)
		{
			for (int i = 5 * u; i < 5 * (u + 1); i++)
			{
				xt[i] = ran->Next(x0[u] - r0[u], x0[u] + r0[u]);
				yt[i] = ran->Next(y0[u] - r0[u], y0[u] + r0[u]);

				if ((x0[u] - xt[i]) * (x0[u] - xt[i]) + (y0[u] - yt[i]) * (y0[u] - yt[i]) > r0[u] * r0[u])
					i--;
			}
		}
	}
	
	void randc()
	{
		Random^ ran = gcnew Random();
		for (int i = 0; i < 3; i++)
		{
			x0[i] = ran->Next(-50, 50);
			y0[i] = ran->Next(-50, 50);
			r0[i] = ran->Next(20, 40);

			if (i > 0)
			{
				for (int u = 0; u < i; u++)
				{
					if (checkc(i, u) == false) i = 0;
				}
			}
		}

	}

	bool checkc(int i, int u)
	{
		double rast = sqrt(pow(x0[i] - x0[u], 2) + pow(y0[i] - y0[u], 2));
		if (r0[i] + r0[u] > rast && r0[i] + rast > r0[u] && r0[u] + rast > r0[i] || (pow(x0[i] - x0[u], 2) + pow(y0[i] - y0[u], 2) < pow(r0[i] - r0[u], 2)))
		{
			return false;
		}
	}

	

	
};
	

[STAThreadAttribute]
void main(array<String^>^ args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	proga::MyForm form;
	Application::Run(% form);


}



System::Void proga::MyForm::ïîñòðîèòüÃðàôèêToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	int a, i, u;
	circle c;
		
	//this->label1->Text = Convert::ToString (x0[0]);

	for (i=0;i<4;i++)
		this->chart1->Series[i]->Points->Clear();

	c.randc();
	
	for (a = 0; a <= 360; a++)
	{
		for (i = 0; i < 3; i++)
		{
			
			int x = c.getx(i) + c.getr(i) * cos(a);
			int y = c.gety(i) + c.getr(i) * sin(a);
			
			this->chart1->Series[i]->Points->AddXY(x, y);
		}
	}
	
	c.randt();

	for (i = 0; i < 15; i++)
	{
		this->chart1->Series[3]->Points->AddXY(c.getxt(i), c.getyt(i));
	}

}

System::Void proga::MyForm::èçÔàéëàToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	char* File = "text.txt";
	int x, y, r, i,a;
	circle c;

	std::fstream fs;
	std::ifstream f(File);
	if (!(f.is_open()))
		MessageBox::Show("Error");
	else
	{
		MessageBox::Show("Ôàéë ïðèíèìàåò çíà÷åíèÿ òîëüêî äëÿ 3 îêðóæíîñòåé");
		this->chart1->Series[3]->Points->Clear();
		while (!f.eof())
		{
			for (i = 0; i < 3; i++)
			{
				this->chart1->Series[i]->Points->Clear();
				f >> x >> y >> r;
				c.setx(i, x);
				c.sety(i, y);
				c.setr(i, r);
				
				if (i > 0)
				{
					for (int u = 0; u < i; u++)
					{
						if (c.checkc(i, u) == false) 
							MessageBox::Show("Îêðóæíîñòè ïåðåñåêàþòñÿ");
					}
				}
			}
			for (a = 0; a <= 360; a++)
			{
				for (i = 0; i < 3; i++)
				{

					int x = c.getx(i) + c.getr(i) * cos(a);
					int y = c.gety(i) + c.getr(i) * sin(a);

					this->chart1->Series[i]->Points->AddXY(x, y);
				}
			}
		}
		f.close();
		c.randt();

		for (i = 0; i < 15; i++)
		{
			this->chart1->Series[3]->Points->AddXY(c.getxt(i), c.getyt(i));
		}

		fs.open("out.txt", std::fstream::out );
		if (fs.is_open())
		{
			fs << "x\ty\n";
			for (i = 0; i < 15; i++)
			{
				fs << c.getxt(i) << "\t" << c.getyt(i) << "\n";
			}
		}
		fs.close();
		

	}

}
