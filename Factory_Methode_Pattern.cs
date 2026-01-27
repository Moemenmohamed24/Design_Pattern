امتي بستخدم ال Factory Method ؟

  المشكلة الأصلية اللي Factory Method اتحلّت عشانها
المشكلة مش:
“أنا عايز أعمل object”
لا.
المشكلة الحقيقية:
“أنا عندي خوارزمية (Algorithm / Workflow) ثابتة
بس نوع كائن واحد جوّه الخوارزمية ده بيختلف”   

بمعني ايه بردو ؟؟
يعني:
  بيكون عبتره عن كود ثابت في الprocces 
  لكن فيه جزء واحد فيه واللي هو جزء انشاء الكائن هو اللي مختلف يعني  	80% من الكود واحد
	20% مختلف
	والاختلاف ده في نوع الكائن المُنشأ


عندي  شرطين علشان هل استخدم factory method or no
الشرط الاول :

1)  عندك Workflow ثابت (Template Method)

مثال للفهم : 

  public Pizza OrderPizza(string type)
{
    Pizza pizza = CreatePizza(type); // الجزء ده هو الوحيد هو اللي متغير علي حسب انا عايز بيتزا نوعها ايه

    if(pizza != null)
    {
        pizza.Prepare();
        pizza.Backe();
        pizza.Cut();
        pizza.Box();
    }

    return pizza;
}

هنا:
•	ترتيب الخطوات ثابت
•	مينفعش يتغير
o	أي بيتزا لازم:    تتعمل  تتجهز تتخبز  تتقطع  تتتحط في العلبة


إيه اللي متغير؟
protected abstract Pizza CreatePizza(string type);

إنشاء البيتزا نفسها

نوعها

ستايلها (NY / Chicago)

وده بيتساب للـ subclasses 

2) لـ Subclasses هي اللي بتقرر نوع الـ Product

كل subclass يعمل override

يعني قرار عمل البيتزا يكون من الكلاس الفرعي مش من الاب

مثال :

  class NYPizzaStore : PizzaStore
 {
هنا الكلاس الفرعي هو اللي بيقرر انشاء البيتزا عن طريق داله CreatePizza
     protected override Pizza CreatePizza(string Type)
     {
         if (Type == "Cheese")  return new NYStyleCheesePizza();

        if (Type == "Veggie") return new NYStyleVeggiePizza();

        return null;
     }
 };





مثال كامل عن Factory method:


using System;

abstract كلاس علشان اعمل كل الدوال المشتركه في اي بيتزا 
 abstract class Pizza
 {
     public abstract void Prepare();
     public abstract void Backe();
     public abstract void Cut();
     public abstract void Box();

 };
ده يعتبر ابستراكت اللي هيعمل البيتزا 
 abstract class PizzaStore
 {
   دي داله الاوردر الخاصه بطلب نوع من البيتزا وفيها نوع البيتزا 
     public Pizza OrderPizza(string type)
     {
     داله انشاء نوع البيتزا نفسها بترجع اوبجيكت ريفرينس ل نوع البيتزا اللي هو اختارها من الكلاس الفرعي 
         Pizza pizza = CreatePizza(type);
الاوبجيكت pizza ده هو اللي بيكون الاوبجيكت اللي فيه نوع البيتزا وبالتالي بيطبق الدوال الخاصه بالبيتزا زي التحضير والخبز عن طريق تعدد الاشكال (
         if(pizza != null)
        {
            pizza.Prepare();
            pizza.Backe();
            pizza.Cut();
            pizza.Box();
        }

        return pizza;
     }

     protected abstract Pizza CreatePizza(string type);

 };

  class NYStyleCheesePizza : Pizza
 {
     public override void Prepare() => Console.WriteLine(" Prepare NY Cheese Pizza");
    public override void Backe() => Console.WriteLine(" Backe NY Cheese Pizza");
    public override void Cut() => Console.WriteLine(" Cut NY Cheese Pizza");
    public override void Box() => Console.WriteLine(" Box NY Cheese Pizza");

 };

 class NYStyleVeggiePizza : Pizza
 {
    public override void Prepare() => Console.WriteLine(" Prepare NY Veggie   Pizza");
    public override void Backe() => Console.WriteLine(" Backe NY Veggie   Pizza");
    public override void Cut() => Console.WriteLine(" Cut NY Veggie  Pizza");
    public override void Box() => Console.WriteLine(" Box NY Veggie  Pizza");

 };

  class ChicagoStyleCheesePizza : Pizza
 {
    public override void Prepare() => Console.WriteLine(" Prepare Chicago  Cheese Pizza");
    public override void Backe() => Console.WriteLine(" Backe Chicago  Cheese Pizza");
    public override void Cut() => Console.WriteLine(" Cut Chicago  Cheese Pizza");
    public override void Box() => Console.WriteLine(" Box Chicago  Cheese Pizza");

 };

  class ChicagoStyleVeggiePizza : Pizza
 {
    public override void Prepare() => Console.WriteLine(" Prepare Chicago Veggie   Pizza");
    public override void Backe() => Console.WriteLine(" Backe Chicago Veggie   Pizza");
    public override void Cut() => Console.WriteLine(" Cut Chicago Veggie  Pizza");
    public override void Box() => Console.WriteLine(" Box Chicago Veggie  Pizza");

 };

  class NYPizzaStore : PizzaStore
 {

     protected override Pizza CreatePizza(string Type)
     {
         if (Type == "Cheese")  return new NYStyleCheesePizza();

        if (Type == "Veggie") return new NYStyleVeggiePizza();

        return null;
     }
 };


class ChicagoPizzaStore : PizzaStore
{
    protected override Pizza CreatePizza(string type)
    {
        if (type == "Cheese") return new ChicagoStyleCheesePizza();

        if (type == "Veggie") return new ChicagoStyleVeggiePizza();

        return null;
    }


};

 class Program
 {
     static void Main(string[] args)
     {
        PizzaStore NYpizza = new NYPizzaStore();

        PizzaStore Chpizza = new NYPizzaStore();

        NYpizza.OrderPizza("Cheese");

        Chpizza.OrderPizza("Veggie");


    }
}



ليه مثال PizzaStore ده Factory Method فعلًا؟
الإجابة في سطر واحد:
لأن قرار إنشاء الـ object متساب للـ subclass
بينما الـ workflow ثابت في الـ superclass
وده هو تعريف Factory Method بالحرف.

