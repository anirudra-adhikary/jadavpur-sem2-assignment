coupons = {
    "Monday":    ("MON10", 10),
    "Tuesday":   ("TUE15", 15),
    "Wednesday": ("WED20", 20),
    "Thursday":  ("THU5",   5),
    "Friday":    ("FRI25", 25),
    "Saturday":  ("SAT30", 30),
    "Sunday":    ("SUN50", 50),
}

day = input("Enter the day of the week (e.g. Monday): ").strip().capitalize()

if day in coupons:
    code, discount = coupons[day]
    print(f"Day      : {day}")
    print(f"Coupon   : {code}")
    print(f"Discount : {discount}%")
else:
    print("Invalid day. Please enter a valid day name (e.g. Monday, Tuesday, ...).")

