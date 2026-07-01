def fibonacci_gen(count):
    a, b = 0, 1
    for _ in range(count):
        next_a, next_b = b, a + b

        print(
            f"  [Generator] Yield: {a:<2} | State: (a={a}, b={b:<2}) → Next State: (a={next_a}, b={next_b})"
        )

        yield a
        a, b = b, a + b

    print("  [Generator] Target count fulfilled. Terminating sequence.")

user_input = input("Enter target sequence length [Press Enter for default 7]: ")
n = int(user_input) if user_input.strip() else 7

gen = fibonacci_gen(n)
fibs = []

print(f"\n--- Execution Trace: Generator Step-Through (n = {n}) ---")

for _ in range(n + 1):
    try:
        val = next(gen)
        fibs.append(val)
    except StopIteration:
        print(
            "  [Main Process] StopIteration caught. Generator object is successfully exhausted."
        )

print(f"\nFinal Sequence Array: {fibs}")