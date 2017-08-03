This project is used to solve problem 1 in column 3. The problem can be described as below:
    Based on 1978 United States Federal Income Tax, the residents in USA will be taxed
        income <= 2200, tax = 0
        income <= 2700, tax = 0.14 * (income - 2200)
        income <= 3200, tax = 70 + 0.15 * (income - 2700)
        income <= 3700, tax = 145 + 0.16 * (income - 3200)
        income <= 4200, tax = 225 + 0.17 * (income - 3700)
        ...
        income > 102200, tax = 53090 + 0.17 * (income - 102200)
