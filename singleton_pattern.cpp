يعني إيه Singleton؟
هو Pattern بيضمن إن:
يبقى فيه نسخة واحدة فقط من الكلاس طول عمر البرنامج
وأي حد يطلب الكلاس → ياخد نفس النسخة.
 
المشكلة من غير Singleton:

تخيل عندك كلاس:

class DatabaseConnection
{
    public DatabaseConnection()
    {
        Console.WriteLine("Database Connected");
    }
}
واستخدمته كده:
var db = new DatabaseConnection(); //   اتصال جديد بموارد جديده بجزء جديد اصلا من العمليات!
var db2 = new DatabaseConnection(); // اتصال تاني بموارد جديده بجزء جديد اصلا من العمليات!
var db3 = new DatabaseConnection(); //  اتصال تالت بموارد جديده بجزء جديد اصلا من العمليات!

النتيجة:
Database Connected
Database Connected
Database Connected

المشاكل:

 3 اتصالات بقاعدة البيانات
استهلاك ميموري زيادة
 تضارب في الـ Transactions
 صعب تتحكم في الـ Connection	


	انت محتاج:
 علشان الكلاس الخاص الداتا بيز ده او الاتصال بالداتابيز بشكل عام هو اتصل واحد بس ماينفعش كذا اوبجيكت يتصلوا بالداتابيز لان كده بيحصل تداخل في المعاملات وبغض النظر عن الميموري اللي بتكون كبيره بسبب انشاء اوبجيكت كتير بيحصل خلل في العمليات اصلا 	 اتصال واحد فقط بالداتابيز
كل البرنامج يستخدم الاتصال ده لكل المعاملات 
	ممنوع حد يعمل نسخة جديدة



هنا ييجي دور Singleton 
الحل باستخدام Singleton
الفكرة:
•	نخلي الـ Constructor خاص (private) علشان محدش يعمل اوبجيكت خالص من الكنستراكتور او اللي عمل من خلال الطريقه اللي متوفره بس.
•	نعمل Instance واحدة فقط 
•	نوفر طريقة للوصول ليها 



	مثال في C#علي Singleton:

public class ConnectionDatabase
{

ده الاوبجيكت اللي هيكون مشترك بين الكل      
    private static ConnectionDatabase _instance;

ده اللوك اللي هيمنع اتنين اوبجيكت يشتغلوا مع بعض  
    private static readonly object _Locke = new object();

هنا عملت الكنستراكتور برايفيت علشان ما فيش حد يعمل نوي اوبجيكت الا من المكان اللي انا محدده ومره واحده بس 

    private ConnectionDatabase()
    {
        Console.WriteLine("Databese Connectede");
    }


دي الداله اللي بناديها علشان اعمل اول اوبجيكت خالص نيو اوبجيكت وبعد اول مره برجع بقا نفس الاوبجيكت اللي اتعمل في اول مره واستخدمه بكده اكون ضامن ان كل البرنامج بيتعامل مع اوبجيكت واحد بس 

    public static ConnectionDatabase Instance()
    {
        get
        {
             lock (_Locke)
             {
                 اول مره هيحصل فيها النيو 
                if( _instance == null)
                {
                    _instance = new ConnectionDatabase();
                }
هنا بقا لما الاوبجيكت يكون اتعمل خلاص وانا عايز اوبجيكت تاني بيرجه الاوبجيكت اللي اتنده بحيث يكون اوبجيكت واحد بس للبرنامج كله 

                return _instance;

             }
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        ConnectionDatabase db1 = ConnectionDatabase.Instance();اول مره هيحصل نيو 
        ConnectionDatabase db2 = ConnectionDatabase.Instance();التاني تيرجع القديم 
        ConnectionDatabase db3 = ConnectionDatabase.Instance();التالته تيرجع القديم

    }
}
 بحيث يكون نفس الاوبجيكت لكل حاجه  Connected  مرة واحدة بس    ***






إمتى أستخدم Singleton؟

استخدمه لما يكون عندك:
✔ Logger
✔ Database Connection
✔ Config Manager
✔ Cache Manager
✔ Thread Pool
✔ Device Driver
✔ Hardware Controller

أي حاجة:
لازم تبقى واحدة فقط في السيستم كله


إمتى ما أستخدموش؟
❌ لو الكلاس ممكن يبقى له أكتر من نسخة
❌ لو محتاج Dependency Injection
❌ لو الكلاس بيتغير حسب المستخدم



امتي تعرف الكلاس ده محتاج Singleton؟
اسأل نفسك 5 أسئلة:
1. هل هو مورد مشترك في التطبيق كله؟
•	نعم → Singleton ✓
•	لا → عادي ✗
2. هل إنشاء أكثر من نسخة يضر بالأداء؟
•	نعم → Singleton ✓
•	لا → عادي ✗
3. هل البيانات فيه عامة ومشتركة؟
•	نعم → Singleton ✓
•	لا (خاصة بمستخدم) → عادي ✗
4. هل يجب أن يكون له حالة واحدة فقط؟
•	نعم → Singleton ✓
•	لا (كل مستخدم له حالة) → عادي ✗
5. هل هو Entity أو DTO؟
•	نعم → عادي ✗
•	لا (manager/service) → Singleton محتمل ✓


