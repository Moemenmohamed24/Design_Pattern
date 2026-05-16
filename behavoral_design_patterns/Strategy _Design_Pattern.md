

# التعريف : 
هو Design Pattern بيخليك تعرّف مجموعة من الـ Algorithms (الخوارزميات أو طرق تنفيذ معينة)، تحطها في Classes منفصلة، وتخلي الـ Object يقدر يبدّل بينهم في الـ Runtime.



# ليه الناس اخترعوه؟
- الناس اخترعته لأنهم كانوا بيواجهوا مشكلة متكررة جداً:
- عندي نفس العملية، بس بتتنفذ بطرق مختلفة، وأنا بحشر كل الطرق دي جوه Class واحد
 - ده كان بيخلي الكود كارثة  صعب تعدّله، صعب تختبره، وصعب تضيف عليه.



# المشاكل اللي كانت موجودة قبله او المشاكل اللي بيحلها ايه:؟

1)	المشكلة الأولى: الـ if/else أو switch المتضخم:
	وصف المشكلة:
لما يكون عندك عملية ليها أكتر من طريقة تنفيذ، بتلاقي نفسك بتحط كل الطرق دي جوه Method واحدة باستخدام if/else أو switch.
	
		
<img width="874" height="727" alt="image" src="https://github.com/user-attachments/assets/4ac66d8a-1a34-4ef9-815f-673e585ae8e7" />

***** لو جاء payment type جديد هنزود else if تاني هنا!

كل ما يتم إضافة طريقة دفع جديدة، لازم نعدل على نفس الـ Class، وده يعتبر مخالفة لمبدأ Open/Closed Principle.
الـ Method بقت كبيرة جدًا وبتجمع أكتر من مسؤولية في مكان واحد، وده يعتبر انتهاك لـ Single Responsibility Principle.
اختبار جزء معين زي PayPal بشكل منفصل بقى صعب بسبب ترابط كل منطق الدفع داخل نفس الكلاس.
أي مشكلة في منطق الـ Credit Card ممكن تأثر على باقي طرق الدفع الموجودة في نفس الملف.
المشاكل المتوقعة لو التصميم الحالي استمر
حجم الـ Class هيكبر بشكل مبالغ فيه مع الوقت.
أي تعديل بسيط ممكن يسبب مشاكل غير متوقعة في أجزاء تانية.
الكود هيبقى أصعب في الصيانة والتطوير والاختبار مستقبلًا.































# مثال بيحل كل المشاكل اللي كانت موجوده :
```cs
//---------------------	Context (السياق)-------------------------
//هو الكلاس المسؤول عن إدارة عملية الدفع، لكنه لا يعرف تفاصيل الدفع نفسها.
//هو فقط:   يحتفظ بطريقة الدفع الحالية 
//	ينفذ عملية الدفع باستخدامها 
//	يقدر يغيّر طريقة الدفع أثناء التشغيل (Runtime) عن طريق method بتعمل كده

public class PaymentProcessor
{

    IpaymentInterface _ipaymentInterface;


    public PaymentProcessor(IpaymentInterface ipaymentInterface)
    {
        _ipaymentInterface = ipaymentInterface;
    }

    public void SetStrategy(IpaymentInterface ipaymentInterface)
    {
        _ipaymentInterface = ipaymentInterface;
    }


    public void pay(decimal ammount)
    {
        _ipaymentInterface.pay(ammount);
    }
}

//------------------------------Strategy Interface  واجهة الاستراتيجية--------------------------
//هي العقد أو القانون اللي كل طرق الدفع لازم تلتزم بيه.
public interface IpaymentInterface
{
    void pay(decimal account);
}

//-----------------------Concrete Strategies (الاستراتيجيات الفعلية)
//دول التنفيذات الفعلية  لكل طريقة. يعني دول اللي لو حبيت ازود طريقه هزودها بطريقه سريعه 
//يعني كل كلاس فيهم بيعمل نفس الوظيفة لكن بأسلوب مختلف.
//دي الطرق المختلفة للدفع، وكل واحدة فيها طريقة تنفيذ مختلفة لنفس العملية.

//اول طريقه للدفع
public class CreditCardPayment : IpaymentInterface
{
    public void pay(decimal amount)
    {
        Console.WriteLine("card...");
        Console.WriteLine("validation...");
        Console.WriteLine("withdrow: " + amount);
    }

}

//الطريقه التانيه للدفع
public class PayPalPayment : IpaymentInterface
{
    public void pay(decimal amount)
    {
        Console.WriteLine("paypal...");
        Console.WriteLine("validation...");
        Console.WriteLine("withdrow: " + amount);
    }
}

//الطريقه الثالثه للدفع
public class CryptoPayment : IpaymentInterface
{
    public void pay(decimal amount)
    {
        Console.WriteLine("crypto...");
        Console.WriteLine("validation...");
        Console.WriteLine("withdrow: " + amount);

    }
}



public class Program
{
    public static void Main()
    {
        //اوبجيكت من نوع انتريفيس , لكن بيأشر علي اوبجيكت من نوع 
        IpaymentInterface sterategy = new CreditCardPayment();

        //ارسال الاوبجيكت علشان يطبق البوليمورفيزم ويطبق داله الانترفيس
        PaymentProcessor process = new PaymentProcessor(sterategy);
        process.pay(4);


       

        //تغيير نوع الدفع في الرن تايم
        process.SetStrategy(new PayPalPayment());
        process.pay(5);

        //تغيير نوع الدفع في الرن تايم
        process.SetStrategy(new CryptoPayment());
        process.pay(6);



    }
}
```



