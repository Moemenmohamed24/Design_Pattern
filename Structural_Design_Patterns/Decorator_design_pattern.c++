
  Decorator Pattern هو نمط تصميم يسمح بإضافة مسؤوليات إضافية لكائن بشكل ديناميكي، ويوفر بديلاً مرناً للوراثة الفرعية لتوسيع الوظائف 
ببساطة: بدل ما تعمل كلاسات كتير بالوراثة، تعمل كلاسات صغيرة تلف بعضها وكل واحد يضيف ميزة جديدة.


نمط تصميم الديكور هو نمط هيكلي يسمح بإضافة سلوكيات إلى الكائنات الفردية بشكل ديناميكي. فهو يعزز الوظائف دون تعديل الفئة الأصلية أو التأثير على الكائنات الأخرى.
•	يستخدم فئات الديكور لتغليف الكائنات الموجودة.
•	يضيف سلوكًا جديدًا في وقت التشغيل بدلاً من وقت الترجمة.
•	يعزز المرونة من خلال تجنب تضخم الفئات الفرعية.
•	يتبع مبدأ الانفتاح/الإغلاق من خلال توسيع الوظائف دون تغيير التعليمات البرمجية الموجودة.



مشاكل بيحلها Decorator:

Tight Coupling → يقلل الترابط بين الكلاسات.
Fragile Base Class → أي تعديل في Base Class مش هيكسر الإضافات. 
Class Explosion → أي تركيبة ممكن تتعمل runtime بدون كلاس جديد.
صعوبة التوسيع → ممكن تضيف ميزات جديدة بسهولة. : لان الكلاسات نش هتكون كبيره او عددها متير


ايه هي خطوات عمل اي ديكوراتور ؟
   الخطوات الأساسية:
الخطوة ️⃣: حدد المشكلة
الخطوة: اعمل الـ Interface الأساسي
الخطوة : اعمل الـ Concrete Component (الكائن الأساسي)
الخطوة : اعمل الـ Base Decorator
الخطوة : اعمل الـ Concrete Decorators (المزينات)
الخطوة : استخدم الـ Decorators


مثال بدون استخدام الديكوراتور :


using namespace std;

// القهوة الأساسية
class Coffee {
public:
    virtual string getDescription() {
        return "Simple Coffee";
    }
    
    virtual double cost() {
        return 10.0;
    }
};

// ===== الآن نبدأ المشكلة! =====

// قهوة بلبن
class CoffeeWithMilk : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Milk";
    }
    
    double cost() override {
        return 10.0 + 3.0;  
    }
};

// قهوة بسكر
class CoffeeWithSugar : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Sugar";
    }
    
    double cost() override {
        return 10.0 + 2.0;  
    }
};

// قهوة بكريمة
class CoffeeWithCream : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Cream";
    }
    
    double cost() override {
        return 10.0 + 5.0;  
    }
};

// قهوة بلبن وسكر
class CoffeeWithMilkAndSugar : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Milk and Sugar";
    }
    
    double cost() override {
        return 10.0 + 3.0 + 2.0;  
    }
};

// قهوة بلبن وكريمة
class CoffeeWithMilkAndCream : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Milk and Cream";
    }
    
    double cost() override {
        return 10.0 + 3.0 + 5.0;  
    }
};

// قهوة بسكر وكريمة
class CoffeeWithSugarAndCream : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Sugar and Cream";
    }
    
    double cost() override {
        return 10.0 + 2.0 + 5.0;  
    }
};

// قهوة بلبن وسكر وكريمة
class CoffeeWithMilkAndSugarAndCream : public Coffee {
public:
    string getDescription() override {
        return "Coffee with Milk, Sugar and Cream";
    }
    
    double cost() override {
        return 10.0 + 3.0 + 2.0 + 5.0;  
    }
};

// قهوة بلبن وشوكولاتة
class CoffeeWithMilkAndChocolate : public Coffee {
    // ...
};

// قهوة بسكر وشوكولاتة
class CoffeeWithSugarAndChocolate : public Coffee {
 
};

// قهوة بلبن وسكر وشوكولاتة
class CoffeeWithMilkAndSugarAndChocolate : public Coffee {

};



int main() {
    // لو الزبون عايز قهوة بلبن وسكر
    CoffeeWithMilkAndSugar coffee1;
    cout << coffee1.getDescription() << " - " << coffee1.cost() << " جنيه\n";
    
    // لو عايز قهوة بكريمة فقط
    CoffeeWithCream coffee2;
    cout << coffee2.getDescription() << " - " << coffee2.cost() << " جنيه\n";
    
    // لو عايز قهوة بلبن وكريمة
    CoffeeWithMilkAndCream coffee3;
    cout << coffee3.getDescription() << " - " << coffee3.cost() << " جنيه\n";
    
    return 0;
}



المشكلة الواضحة:
•	3 إضافات → 8 كلاسات
•	4 إضافات → 16 كلاس
•	5 إضافات → 32 كلاس
•	10 إضافات → 1024 كلاس


وده بيخلي الكود كبير جدا وهش جدا اي تعديل في الكلاس الاساسي بيكسر الابناء 


  وده بيؤدي ل Fragile Base Class  
ودي مشكله كبيره بردو بتخترق مبدا open / close principal  


مشكلة الكلاس الأساسي الهش هي أن التعديلات التي تبدو آمنة على الكلاس الأساسي قد تسبب خللاً في الكلاسات المشتقة
المشكلة:
أي تعديل “بسيط” في الـ Base Class ممكن يكسر الـ Derived Classes بدون ما تاخد بالك.
يعني أنت عدلت حاجة شكلها آمنة بس الكلاسات اللي وارثة اتكسرت



  
  الحل: Decorator Pattern

//الكلاس الاساسي او الحاجه اللي انا عايزها بالدوال الاساسيه اللي هي بتعملها 
//Interface الأساسي
class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;
    virtual ~Coffee() = default;
};

//Concrete Component (الكائن الأساسي)
//نوع اساسي من القهوه ده نوع بدون اي اضافات من القهوه
class SimpleCoffee : public Coffee {
public:
    string getDescription() override {
        return "Simple Coffee";
    }

    double cost() override {
        return 10.0;  
    }
};

//Base Decorator
//ده الديكوراتور المسئول عن التزيين 
class CoffeeDecorator : public Coffee {
protected:
    unique_ptr<Coffee> coffee;  

public:
    CoffeeDecorator(unique_ptr<Coffee> c)
        : coffee(move(c)) {}
};

//نوع اضافه 
class MilkDecorator : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    string getDescription() override {
        return coffee->getDescription() + " + Milk";
    }

    double cost() override {
        return coffee->cost() + 3.0;
    }
};

//نوع اضافه 

//__________ Concrete Decorators (المزينات)______
class SugarDecorator : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    string getDescription() override {
        return coffee->getDescription() + " + Sugar";
    }

    double cost() override {
        return coffee->cost() + 2.0;
    }
};

//نوع اضافه 

class CreamDecorator : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    string getDescription() override {
        return coffee->getDescription() + " + Cream";
    }

    double cost() override {
        return coffee->cost() + 5.0;
    }
};

//نوع اضافه 

class ChocolateDecorator : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    string getDescription() override {
        return coffee->getDescription() + " + Chocolate";
    }

    double cost() override {
        return coffee->cost() + 4.0;
    }
};

//نوع اضافه 

class CaramelDecorator : public CoffeeDecorator {
public:
    using CoffeeDecorator::CoffeeDecorator;

    string getDescription() override {
        return coffee->getDescription() + " + Caramel";
    }

    double cost() override {
        return coffee->cost() + 6.0;
    }
};


int main() {
    //قهوه عادديه 
    unique_ptr<Coffee> order1 = make_unique<SimpleCoffee>();
    cout << order1->getDescription() << endl;
         cout << "price: " << order1->cost() ;

  //قهوه مع لبن 
    unique_ptr<Coffee> order2 = make_unique<SimpleCoffee>();
    order2 = make_unique<MilkDecorator>(move(order2));
    cout << order2->getDescription() << endl;
         cout << "price: " << order2->cost() ;

  //قهوه مع لبن مع سكر 
    unique_ptr<Coffee> order3 = make_unique<SimpleCoffee>();
    order3 = make_unique<MilkDecorator>(move(order3));
    order3 = make_unique<SugarDecorator>(move(order3));
    cout << order3->getDescription() << endl;
         cout << "price: " << order3->cost() ;

  //قهوه مع لبن مع سكر مع كريمه
  
    unique_ptr<Coffee> order4 = make_unique<SimpleCoffee>();
    order4 = make_unique<MilkDecorator>(move(order4));
    order4 = make_unique<SugarDecorator>(move(order4));
    order4 = make_unique<CreamDecorator>(move(order4));
    cout << order4->getDescription() << endl;
     cout << "price: " << order4->cost() ;
    
      //قهوه مع لبن مع كراميل مع سطلاته مع كريمه مع سكر 
   
    unique_ptr<Coffee> order5 = make_unique<SimpleCoffee>();
    order5 = make_unique<MilkDecorator>(move(order5));
    order5 = make_unique<SugarDecorator>(move(order5));
    order5 = make_unique<CreamDecorator>(move(order5));
    order5 = make_unique<ChocolateDecorator>(move(order5));
    order5 = make_unique<CaramelDecorator>(move(order5));
    cout << order5->getDescription() << endl;
    cout << "price: " << order5->cost() ;
    

  
    unique_ptr<Coffee> order6 = make_unique<SimpleCoffee>();
    order6 = make_unique<ChocolateDecorator>(move(order6));
    order6 = make_unique<CaramelDecorator>(move(order6));
    cout << order6->getDescription() << endl;
    cout << "price: " << order6->cost() ;
    
    return 0;
}
