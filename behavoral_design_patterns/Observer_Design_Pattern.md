 أولاً: ما هو Observer Pattern؟
تخيل إنك مشترك في قناة يوتيوب — لما صاحب القناة ينزّل فيديو جديد، انت بتاخد نوتيفيكيشن تلقائياً من غير ما تروح تشوف القناة كل يوم.
ده بالظبط الـ Observer Pattern.
التعريف: هو نمط تصميمي يسمح لـ object واحد( الـ Subject أو ( Publisher إنه يُخطر مجموعة من الـ objects التانية الـ     (Observers or Subscribers) تلقائياً لما تحصل تغييرات في حالته.
الـ object ( الـ Subject أو ( Publisher: ده اللي بيتم مراقبته هو اللي بيقع عليه الفعل او هو المفعول به
الـ     (Observers or Subscribers): هما اللي بيراقبوا الاوبجيكت او بمعني اصح هما الفعل اللي بيعموا فعل المراقبه

# الفكره:
عندك publisher (اللي بيحصل فيه التغيير)، وعندك subscribers (اللي عاوزين يعرفوا بالتغيير ده). الـ publisher مش محتاج يعرف مين هم — وهم مش محتاجين يتصلوا به باستمرار. في الوسط: عقد اشتراك.



#  طب ايه المشاكل اللي ال observer ظهر علشانها وعلشان يحلها ؟
#  1 ) المشكلة الأولى: Tight Coupling  الارتباط الشديد

ايه هي Tight Coupling؟
ببساطة، tight coupling يعني إن كود كلاس معين مثلاً  Stock عارف التفاصيل الداخلية لكل كلاس تاني هيشتغل معاه، وبيستدعيها مباشرة بالاسم والطريقة (method) بالظبط.
يعني الكلاس مش بيتعامل مع واجهة عامة أو عقد (contract)، لكنه مرتبط بتنفيذ محدد مع الكلاسات اللي بيتعامل معاها مباشر

```cs
public class Stock
{
    private decimal _price;
    private PriceDisplay _display;    // عارف بالاسم
    private MobileApp _mobileApp;     
    private AnalysisSystem _analysis; 

    public Stock()
    {
        _display  = new PriceDisplay();
        _mobileApp = new MobileApp();
        _analysis = new AnalysisSystem();
    }

    public void SetPrice(decimal price)
    {
        _price = price;
        _display.Show(price);      // ارتباط مباشر
        _mobileApp.Push(price);    
        _analysis.Process(price);  
    }
}
```
