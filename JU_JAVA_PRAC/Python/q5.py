def fibonacci_gen():
    a, b = 0, 1
    while True:
        print(f"[Trace] Generating: {a}")
        yield a
        a, b = b, a + b

if __name__ == "__main__":
    try:
        count = int(input("How many Fibonacci numbers would you like to generate? "))
        fib = fibonacci_gen()
        sequence = [next(fib) for _ in range(count)]
        print(f"First {count} Fibonacci numbers:", sequence)
    except ValueError:
        print("Please enter a valid integer.")