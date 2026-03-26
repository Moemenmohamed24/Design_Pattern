Proxy Design Pattern:
نمط تصميم الوكيل هو نمط تصميم هيكلي حيث يعمل كائن الوكيل كعنصر نائب للتحكم في الوصول إلى الكائن الأصلي. يتواصل العميل مع الوكيل، الذي بدوره يوجه الطلبات إلى الكائن الأصلي. كما يمكن للوكيل توفير وظائف إضافية مثل التحكم في الوصول، والتهيئة المؤجلة، والتسجيل، والتخزين المؤقت.

•	يساعد في إدارة الوصول إلى الكائنات الحساسة أو التي تستهلك موارد كثيرة دون الكشف عن تفاصيلها الداخلية.
•	يحسّن الأداء عن طريق تأخير إنشاء الكائنات من خلال التحميل الكسول.
•	يسمح بإضافة مسؤوليات إضافية (مثل الأمن أو التسجيل) دون تعديل الكائن الحقيقي.


  ببساطة:
Proxy هو كلاس وسيط (وسيط ذكي) بيقف بينك وبين الكائن الحقيقي (Real Object) علشان يتحكم في الوصول ليه.
يعني بدل ما تتعامل مباشرة مع object تقيل أو حساس، بتتعامل مع Proxy.


  
//--------المشاكل اللي تم اختراعه علشانها:-----------//        

//-------------المشكلة الأساسية Object تقيل جدًا (Heavy Object) : Expensive Object :(1-----------//    
  تخيل عندك object زي:
•	صورة ضخمة (MBs أو GBs)
•	اتصال بـ database
•	ملف كبير
•	API request تقيل
المشكلة مش في وجوده
المشكلة في توقيت تحميله (Timing of Initialization)
هو إنك:
تنشئ Object في وقت إنشائه (construction time)
بدل ما تنشئه وقت استخدامه (usage time)

  خلاصه المشكله:
  ان انا مش عايز انشئ الكائن واستخدم الذاكره واستهلك وقت وفي الاخر مااستخدموش اصلا


نقطه مهمه:
أنت مش بتقلل وقت التحميل
 احنا بنقلل عدد التحميل الغير مفيد , بمعني لو انا حملت او عملت 100 اوبجيكت واستخدمت منهم 5 انا بمنع تحميل ال 95 الي انا مااستخدمتهمش أنت بتقلل عدد مرات التحميل غير الضرورية



//--------التطبيق  لاول مكشله :-----------//    
  
//-------- من غير استخدام البروكسي :-----------//    


المشكلة: كل الفيديوهات بتتحمل من البداية

  
class video
{
public:

    string _path;
    video(string path)
    {
        _path = path;
        leadfromDisk(path);
    }



    void play()
    {
        cout << "start play video " << "with path " << _path << "\n";
    }


private:

   void leadfromDisk(string path)
   {
       cout << "loaded video from disk -> " << path << "\n \n";
   }
};


int main() {

    //هنا انا حملت كل الفيديوهات في مره واحده او حملتهم اصلا بس لو بصينا تحت هنلاقي اني اصلا مشغل فيديو واحد بس , يبقي انا كده اخدت من الذاكره وبطأت العمليه صح 
    vector<video> playlist;

    playlist.push_back(video("moving.mp4"));
    playlist.push_back(video("intro.mp4"));
    playlist.push_back(video("end.mp4"));

    //اهو لو بصيت هنا هتلاقي اني  مستخدم فيديو واحد بس مع اني  حملت كل الفيديوهات 
    playlist[2].play();
//المشكله بقا طب ليه من الاول احمل كل الفيديوهات دي طب مانا اشتغل بس اني احمل اللي انا عايزه بس
    return 0;
}


رغم إن المستخدم شغّل فيديو واحد بس:
•	كل الفيديوهات اتحملت 
•	CPU 
• Memory wasted 
•	startup بطيء 


//--------------------------------------------------------------------------بعد (Lazy Initialization باستخدام Proxy)------------------------------------------------------------//
بعد (Lazy Initialization باستخدام Proxy)

class video
{

public:
    string _path;
    video(string path)
    {
        _path = path;
        leadfromDisk(path);
    }


    void play()
    {
        cout << "start play video " << "with path " << _path << "\n";
    }


private:

   void leadfromDisk(string path)
   {
       cout << "loaded video from disk -> " << path << "\n \n";
   }
};



// that is proxy
class VideoProxy
{
public:
    video *_realVideo;
    string _path;

    VideoProxy(string path) : _realVideo(nullptr)
    {
        _path = path;
    }

    void play()
    {
        if (_realVideo == nullptr)
        {
            _realVideo = new video(_path);
        }

        _realVideo->play();
    }
};


int main() {

    // هنا بقا انا مش بنشئ او مش بحمل كل الفيديوهات لا انا بس بحط متغيراتهم في فيكتور ولما اخلص بشوف بقا من البلاي ليست انا عايز ايه منهم , هنا بقا بيتحدد مين اللي يتنشأ عن طريق اني بشغل ال play  
    vector<VideoProxy> playlist;


    //اهو هنا انا بس بتعامل مع البروكسي بس هنا اذا هنا انا بقلل الوقت بتاع ان شاء او تحميل كل الفيديوهات بعدين اختار لا انا اول لما بختار هو بيتنشأ 
    playlist.push_back(VideoProxy("moving.mp4"));
    playlist.push_back(VideoProxy("intro.mp4"));
    playlist.push_back(VideoProxy("end.mp4"));


    //هنا وقت اختيار الفيلم اللي هو وقت التحميل اللي هو وقت الانشاء هنا انا حملت اللي انا عايزه بس ,  انما في المره اللي فاتت انا حملت ال 3 بعدين اختارت 
    playlist[2].play();
//this == &playlist[1]

    return 0;
}

فوائد الاستخدام ؟؟
 توفير الذاكرة (Memory Efficiency)
•	قبل: كل object تقيل يتحمّل فورًا، حتى لو مش مستخدم 
•	بعد: Proxy خفيف جدًا، البيانات الحقيقية تتحمّل لما تحتاجها بس 
•	النتيجة: استهلاك RAM أقل، خصوصًا لو عندك آلاف العناصر 
  
 تحسين سرعة البداية (Startup Performance / Responsiveness)
•	قبل: التطبيق يقعد يحمل كل شيء من البداية → slow startup 
•	بعد: التطبيق يفتح بسرعة، تحميل العناصر الثقيلة بيتأجّل حتى الاستخدام الفعلي 

 تحسين استهلاك المعالج (CPU Efficiency)
•	التحميل والتجهيز للـ objects الثقيلة بيتأجل → CPU مش بيشتغل على حاجات مش مستخدمة 
 تخفيف الضغط على الـ I/O (Disk / Network)
•	قبل: كل الملفات تتقرأ من القرص فورًا → ضغط على disk / network 
•	بعد: الملفات تتحمل عند الحاجة فقط → I/O أقل 

   //--------------المشكلة 2): التحكم في الوصول (Access Control / Security):-----------------//

   السيناريو الواقعي
تخيل عندك Object حساس زي:
•	ملف إعدادات نظام 
•	كائن يمثل حساب بنكي 
•	واجهة API تتحكم في بيانات مستخدمين 
•	فيديو خاص أو محتوى مدفوع
يعني اي  حد ممكن يستخدمه او يغير فيه او يستخدم اللي جواه بمعني اصح


//----------------------------------  المثال الغلط قبل الـ Proxy المشكلة:---------------------------------//

class BankAccount
{
    string _wonerName = " ";
    double _balance = 0.0;


public:
    BankAccount(string woner ) : _wonerName(woner) , _balance(1000) {}
    
    void withdraw(int ammount)
    {
        _balance -= ammount;
        cout << "Withdrawn: " << ammount << endl;
        cout << "Remaining balance: " << _balance << endl;
    }

};



int main() {
    //هنا انا بعت مؤمن ومؤمن ده مش ادمن اصلا علشان يتعامل مع الداله دي او الكلاس بانك اكونت , فده غلط مافيش حماية خالص 
    BankAccount bankAccount("moemen");

    //بص هنا اهو انا سحبت فلوس وانا اصلا مش من حقي اني اعمل كده
    bankAccount.withdraw(500);
   
    return 0;
}



//----------------------------------بعد الـ Proxy الحل:--------------------------------------//

class BankAccount
{
    string _wonerName = " ";
    double _balance = 0.0;

public:
    BankAccount(string woner ) : _wonerName(woner) , _balance(1000) {}
    
    void withdraw(int ammount)
    {
        _balance -= ammount;
        cout << "Withdrawn: " << ammount << endl;
        cout << "Remaining balance: " << _balance << endl;
    }

};



//هو ده بقا البروكسي اللي هيكون وسيط بين ال البانك اكونت و الكلاينت نفسه
//proxy
class BankAccountProxy
{
private:
    BankAccount* bankAccount;

    string _currentUser;
    string _owner;

public:
    BankAccountProxy(string currentUser, string owner) : _currentUser(currentUser) , _owner(owner) {}

    void withdraw(int ammount)
    {
        //لو هو مش ادمن الشرط ده هيتحقق وهيخرج برا الداله اصلا من الاساس
        if (_currentUser != _owner)
        {
            cout << " Access Denied for user :" << _currentUser << "\n";
            return;
        }
        //هنا بقا لو هو ادمن يبقي هيشغل عادي الداله يبقي هو ليه صلاحيه في التعامل مع الداله دي
         BankAccount bankAccount(_owner);
        bankAccount.withdraw(ammount);
    }

~BankAccountProxy() {
    delete bankAccount;
};



int main() {
   //هنا انا استخدمت البروكسي الاول علشان اتأكد لو كان هيكون اي حد هيستخدم الويثدرو ولا لا , لو فيه حد غير الادمن يبقي مش هينفع وهيطلع غلط زي المثال اللي تحت ده
    BankAccountProxy bankAccountProxy("moemen","admin");
      bankAccountProxy.withdraw(500);
  
   //هنا بقا عديت علي بروكسي بردو الاول لكن هنا مش هيدي خطا لان اصلا الادمين هو اللي هيستخدم الداله من الاساس
      BankAccountProxy bankAccountProxy("admin", "admin");
      bankAccountProxy.withdraw(500);     

    return 0;
}
ده بقا اللي بيكون وسيط بين البانك اكونت و الكلاينت بحيث مش اي حد في الكلاينت يعرف يستخدم ال withdraw هو واحد بس اللي يعرف  اللي هو Admin



//--------------------المشكلة 4: Caching (مهمة جدًا-------------------------------//
السيناريو:
•	بتجيب data من API 
•	نفس الطلب بيتكرر
المشكلة:
•	latency عالي 
•	load على السيرفر , يعني انا كل مره بجيب نفس البيانات من نفس الحاجه وبخزنها في حاجه معينه    

string GetUserData(short userID)
{
    //Access Control (Authorization)
    //Access Control → يمنع غير admin
    if (_currentUser != "admin")
    {
        return  "access denied for user " + _currentUser  ;
            
    }
//------------------------Caching → ما يطلبش من السيرفر كل مرة-----------------------------//
    if (iscached)
    {
        cout << "returning data from caching \n";
        return cacheddata;
    }

    //Lazy Initialization (اتصال بالسيرفر عند الحاجة)
    //Lazy Loading → ما يعملش connection غير عند الحاجة
    if (!servier)
    {
        cout << "connecting server...  " << "\n";
        servier = new RemoteService();
    }


    cout << "sending to server...  " << "\n";

    cacheddata = servier->GetUserData(userID);
    iscached = true;

    return cacheddata;
}

//--------------------------السوال المهم بقا امتي استخدم الفانكشن العاديه وامتي استخدمم البروكي-----------------------------------// 
إمتى تستخدم كل واحدة؟
 استخدم Functions لو:
•	مشروع صغير 
•	logic بسيط 
•	مفيش تغيير متوقع 
  
 استخدم Classes + Proxy لو:
•	فيه Remote services 
•	فيه احتمالية تغيير 
•	عايز testability 
•	system هيكبر


