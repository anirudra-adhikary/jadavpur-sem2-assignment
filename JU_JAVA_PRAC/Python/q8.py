n = int(input("Enter the upper limit N (default 50): ") or 50)
multiples = list(filter(lambda x: x % 5, range(1, n + 1)))
print(f"Multiples of 5 up to {n}: {multiples}")