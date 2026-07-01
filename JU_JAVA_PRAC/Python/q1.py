def generate_primes(n):
    primes = []
    num = 2

    while len(primes) < n:
        for p in primes:
            if num % p == 0:
                break
        else:
            primes.append(num)
            yield num
        num += 1


limit = int(input("Enter the number of primes to generate: "))

for prime in generate_primes(limit):
    print(prime, end=" ")

print()