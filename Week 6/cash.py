# get input from user
while True:
    try:
        dollars = float(input("Change : "))
        if dollars > 0:
            break
    except ValueError:
        continue

# convert to cent
cents = round(dollars * 100)
count = 0

# Quarters
while cents >= 25:
    cents = cents - 25
    count += 1

# Dimes
while cents >= 10:
    cents = cents - 10
    count += 1

# Nickels
while cents >= 5:
    cents = cents - 5
    count += 1

# Dimes
while cents >= 1:
    cents = cents - 1
    count += 1

print("Total coins: ", count)