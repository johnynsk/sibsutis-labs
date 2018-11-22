resA = [];
resB = [];
resC = [];
mass = [3, 5, 8];
costs = [7, 12, 20];
weight = 25;
ipath = 0;

for i in range(0, weight + 1):
    M = [];
    S = [];
    for j in range(0, len(mass)):
        if (i - mass[j] >= 0):
            M.append(resA[i - mass[j]] + costs[j]);
            S.append(i - mass[j]);
    if len(M) == 0:
        resA.append(0);
        resB.append(0);
        resC.append(0);
        continue

    resA.append(max(M));
    resB.append(M.index(max(M)));
    resC.append(S[M.index(max(M))]);

for i in range(0, weight + 1):
    print [i, resA[i], resB[i], resC[i]]
ipath = weight;
path = [];
product = [];
products = mass;
while ipath <> 0:
    path.append(ipath);
    product.append(resB[ipath]);
    ipath = resC[ipath];

for i in range(0, len(mass)):
    products[i] = 0;

for i in range(0, len(product)):
    products[product[i]] = products[product[i]] + 1

for i in range(0, len(products)):
    print str(products[i]) + " products with mass " + str(mass[i]) + " and costs " + str(costs[i])

print [product, path];

