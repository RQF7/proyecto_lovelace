# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt

plt.rc('xtick',  labelsize=15)
plt.rc('ytick',  labelsize=15)
plt.rc('axes',   labelsize=18)
plt.rc('axes',   titlesize=21)    
'''
Pérdidas debidas al fraude de comercio en línea en Estados Unidos y Canadá,
desde 2001 hasta el 2012 en miles de millones de dólares (<<USD billions>>).

Fuente:
J.S. Kiernan, "Credit Card & Debit Card Fraud Statistics", [online]
WalletHub, 2017
https://wallethub.com/edu/credit-debit-card-fraud-statistics/25725/

'''
revenueLost = [
  1.7,  2.1,  1.9,  2.6,  2.8,  3.1,  3.7,  4.0,  3.3,  2.7,  3.4,  3.5]
year = [
  2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011, 2012]

plt.plot(year, revenueLost, color='black', linewidth=3)
plt.ylabel('Pérdidas en miles de millones de dólares')
plt.xlabel('Año')
plt.title('Pérdidas por año debidas al fraude en línea (comerciantes en ' +
  'EE.UU. y Canadá)')
plt.grid(True)
plt.show()

'''
Pérdidas debidas a los fraudes de tarjetas bancarias en EE.UU de 2012 a 2018
en miles de millones de dólares (<<USD billions>>).
Como la fuente pone estimaciones hasta el 2018, aquí se incluyen solo los datos
recolectados, no los extrapolados.

Fuente:
J. Steele, "Credit card fraud and ID theft statistics" [online], Credit cards,
2017,  https://www.creditcards.com/credit-card-news/credit-card-security-id-theft-fraud-statistics-1276.php

S/A, "Value of payment card fraud losses in the United States from 2012
to 2018, by type (in billion U.S. dollars)" [online], satista, 2015,
https://www.statista.com/statistics/419628/payment-card-fraud-losses-usa-by-type/
'''

cnpLost_rec = [2.1,  2.6,  2.8,  2.9]
year_rec    = [2011, 2012, 2013, 2014]
cnpLost_ext = [2.9,  3.1,  3.8,  5.2,  6.4]
year_ext    = [2014, 2015, 2016, 2017, 2018]
plt.plot(year_rec, cnpLost_rec, color='black', linewidth=3)
plt.plot(year_ext, cnpLost_ext, color='grey',  linewidth=3)
plt.ylabel('Pérdidas en miles de millones de dólares')
plt.xlabel('Año')
plt.title('Pérdidas debido a fraudes con tarjetas no presentes en EE. UU.')
plt.grid(True)
plt.show()
