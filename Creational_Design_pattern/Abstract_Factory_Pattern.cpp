Abstract Factory:
أي جزء في السيستم يعتمد على مجموعة قرارات متعلقة ببعض
لازم تتاخد في مكان واحد 
زي مثلا 

المشكلة الأساسية (ليه النمط ده اتعمل؟):
تخيّل عندك برنامج:
بيشتغل على أنظمة تشغيل مختلفة
وكل نظام تشغيل ليه شكل UI مختلف
وكل UI عبارة عن مجموعة عناصر مترابطة


عندك تطبيق بيشتغل على:
•	Windows    macOS    Linux
كل نظام محتاج:  Button بشكل مختلف    Dialog بشكل مختلف    Checkbox بشكل مختلف


من غير Abstract Factory:

void createUI(string os) {
    if (os == "Windows") {
        WindowsButton* btn = new WindowsButton();
        WindowsDialog* dlg = new WindowsDialog();
        WindowsCheckbox* chk = new WindowsCheckbox();
    }
    else if (os == "macOS") {
        MacButton* btn = new MacButton();
        MacDialog* dlg = new MacDialog();
        MacCheckbox* chk = new MacCheckbox();
    }
    else if (os == "Linux") {
        LinuxButton* btn = new LinuxButton();
        LinuxDialog* dlg = new LinuxDialog();
        LinuxCheckbox* chk = new LinuxCheckbox();
    }
}

المشاكل اللي بتحصل !!
  createUI بقت عارفة تفاصيل أكتر من اللازم (أنظمة تشغيل + عناصر UI + تنفيذ)، وده خلّاها تشيل مسؤوليات مش بتاعتها.
كده حصل تشتت مسؤوليات وكسر لمبدأ Single Responsibility لأنها بتتغير لأكتر من سبب.
أي إضافة OS أو عنصر جديد بتجبرك تعدل كود قديم، وده كابوس صيانة.
وبكده اتكسر كمان مبدأ Open/Closed: الكود لا هو مقفول للتعديل ولا مفتوح للإضافة.


  الحل الصح  (Abstract Factory):


 #include <iostream>
using namespace std;

// 1️⃣ المنتجات المجرّدة (Abstract Products) او الباكدج اللي بتكون مع بعض لما تيجي تعمل او لما بيحصل بشكل تلقائي تغيير في الواجهة علي حسب النظام لو ويندوز او ماك
class Button
{
public:

	virtual void render() = 0;
	virtual void onClick() = 0;
	virtual ~Button() = 0;
};

class Dialog
{
public:
	virtual void show() = 0;
	virtual void close() = 0;
	virtual ~Dialog() = 0;

};

class Chickbox
{
public:
	virtual void check() = 0;
	virtual void uncheck() = 0;
	virtual ~Chickbox() = 0;
};


// 2️⃣ المنتجات الفعلية - Windows Family
class WindowsButton :public  Button
{
public:
	void render() override {
		cout << " Rendering Windows-style button\n";
	}
	void onClick() override {
		cout << " Windows button clicked with visual feedback\n";
	}

};

class WindowsDialog : public Dialog
{
	void show() override {
		cout << " Showing Windows-style dialog with Aero theme\n";
	}
	void close() override {
		cout << " Closing Windows dialog with animation\n";
	}
};

class WindowsChickbox :public Chickbox
{
	void check() override {
		cout << " Windows checkbox checked\n";
	}
	void uncheck() override {
		cout << " Windows checkbox unchecked\n";
	}
};


// 3️⃣ المنتجات الفعلية - macOS Family
class MacButton :public Button
{
public:
	void render() override {
		cout << "Rendering macOS Aqua-style button\n";
	}
	void onClick() override {
		cout << " macOS button clicked with smooth animation\n";
	}

};

class MacDialog :public Dialog
{
	void show() override {
		cout << " Showing macOS sheet dialog\n";
	}
	void close() override {
		cout << " Closing macOS dialog with slide animation\n";
	}
};

class MacChickbox :public Chickbox
{
	void check() override {
		cout << " macOS checkbox checked with checkmark\n";
	}
	void uncheck() override {
		cout << " macOS checkbox unchecked\n";
	}
};

// 4️⃣ المصنع المجرّد (Abstract Factory)
class GUIFactory
{
public:
	virtual Button* CreatButton() = 0;
	virtual Dialog* CreatDialog() = 0;
	virtual Chickbox* CreatChickbox() = 0;

	virtual ~GUIFactory() = 0;

};



// 5️⃣ المصانع الفعلية (Concrete Factories)
class WindowsFactory :public GUIFactory
{
public:

	Button* CreatButton() override
	{
		return new WindowsButton();
	}

	Dialog* CreatDialog() override
	{
		return new WindowsDialog();
	}

	Chickbox* CreatChickbox() override
	{
		return new WindowsChickbox();
	}

};


class MacFactory : public GUIFactory
{
public:

	Button* CreatButton() override
	{
		return new MacButton();
	}

	Dialog* CreatDialog() override
	{
		return new MacDialog();
	}

	Chickbox* CreatChickbox() override
	{
		return new MacChickbox();
	}
};


// 6️⃣ الكود العميل او الداله اللي هيتبعت  فيها نوع النظام 
void creatGUI(GUIFactory* factory)
{

	Button* BUT = factory->CreatButton();
	Dialog* Dia = factory->CreatDialog();
	Chickbox* Chic = factory->CreatChickbox();


	BUT->render();
	BUT->onClick();

	Dia->show();
	Dia->close();

	Chic->check();
	Chic->uncheck();


	delete BUT;
	delete BUT;
	delete BUT;

}


int main()
{
	string operatingSys;
	cout << "inter operatingSys \n[windos , mac]";
	cin >> operatingSys;
	GUIFactory* factory;

	if (operatingSys == "windos")
	{
		factory = new  WindowsFactory();
	}
	else if (operatingSys == "mac")
	{
		factory = new  MacFactory();
	}

	creatGUI(factory);
	
}


(Abstract Factory) هنا حل مشكلة حقيقية في أي برنامج GUI متعدد المنصات:

   و عايز اضيف نظام جديد الموضوع سهل ومش هستخدم شرط تاني وده بيحقق المرونة في إضافة أنظمة جديدة
الداله الخاصه بالانشاء مش عارفه هي بتستخدم كلاس ايع بالظبط في بتنشئ واجهه بس بتاعه مين بقا علي حسب النظام اللي هيكون وده فصل العميل عن التفاصيل
