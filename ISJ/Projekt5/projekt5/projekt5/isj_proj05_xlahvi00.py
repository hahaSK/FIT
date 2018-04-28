#!/usr/bin/env python3
from operator import add 

class Polynomial(object):
    def __init__(self, *coefficients, **kwargs):
        """ Initialize Polynomial class. """

        try:
            if len(kwargs) != 0: #When input in kwargs
                self.coefficients = Polynomial.getCoefficientsFromKwargs(self, **kwargs)
                self.report = self.__str(self.coefficients, self.degree)
            else:    
                hash(coefficients) 
                self.degree = len(coefficients) - 1
                self.coefficients = coefficients
                self.report = self.__str(self.coefficients, self.degree)
        except TypeError:   #if input is a list
            self.coefficients = list(filter(None, coefficients))
            self.coefficients = coefficients[0]
            self.degree = len(self.coefficients) - 1
            self.report = self.__str(self.coefficients, self.degree)
        
    def getCoefficientsFromKwargs(self, **kwargs):
        """ Get coefficients when input values are in kwargs. """
        degree = [i for i in kwargs.keys()]
        degree.sort()
        degree = [str(i).replace("x","") for i in degree] #remove all x
        degree = list(map(int, degree))
        self.degree = degree[len(degree) - 1]
        
        coefficients = []    
        for i in range(0, self.degree + 1):    
            try:
                coefficients.append(kwargs['x' + str(i)])
            except KeyError:
                coefficients.append(0)
              
        return coefficients

      


    def __str(self, coefficients, degree):
        """ Return the polynome as string. """
    
        list_of_polynomes = [' - ' + str(abs(coefficients[k])) + 'x^' + str(k) if coefficients[k] < 0 else ' + ' + str(coefficients[k]) + 'x^' + str(k) for k in range(0,degree + 1) if coefficients[k] != 0]
        
        if not list_of_polynomes:
            return "0"

        list_of_polynomes = list_of_polynomes[::-1] #Invert the list
 
        polynome = ''.join(list_of_polynomes) #From list to string
        polynome = polynome.replace("x^0", "")
        polynome = polynome.replace("x^1", "x")
        polynome = polynome.replace("1x", "x")
        #Strip out leading +
        return polynome.lstrip(' + ')
    
    def __add(self, other):
        """Adds two polynomials."""

        #Max length of polynomials' coefficient lists
        degree = max(self.degree, other.degree) + 1
        self_new_coefficients = list(self.coefficients) + [0]*(degree-self.degree-1)
        other_new_coefficients = list(other.coefficients) + [0]*(degree-other.degree-1)
        #Sum coefficient lists elementwise
        return Polynomial(list(map(add, self_new_coefficients, other_new_coefficients)))   

    def _pow(self, next_self):
        """ Calculate the power of polynome. """
        
        degree = self.degree + next_self.degree
        new_coefficients = [0] * (degree + 1)
        for i in range(0, self.degree + 1):
            for j in range(0, next_self.degree + 1):
                #representing formula a^2+2ab+b^2
                new_coefficients[i + j] += self.coefficients[i] * next_self.coefficients[j] 

        return Polynomial(new_coefficients)

    def derivative(self):
        """ Derivate polynome. """
        
        self.degree = self.degree - 1
        derivated_coefficients = []
        exponent = 1
        for i in range (1, len(self.coefficients)):
            derivated_coefficients.append(self.coefficients[i] * exponent)
            exponent += 1
        return Polynomial(*derivated_coefficients) 
    
    def at_value(self, *arg):
        """ Evaluate polynomial at given x. """
        
        if len(arg) == 2: 
            second_param = self.report.replace("x", '*(' + str(arg[1]) + ')') #replace x for input argument
            second_param = second_param.replace("^", "**")
            second_param = eval(second_param)    
            
            first_param = self.report.replace("x", '*(' + str(arg[0]) + ')')
            first_param = first_param.replace("^", "**") 
            first_param = eval(first_param)

            result = second_param - first_param 
        else:
            result = self.report.replace("x", '*(' + str(arg[0]) + ')') #replace x for input argument
            result = result.replace("^", "**")
            result = eval(result)

        return result   
      
        
#-----------Override methods-----------#

    def __repr__(self):
        """ Method return string representing the polynomial. """
        
        return self.report

    def __eq__(self, other):
        """ Override the == operator. """
        
        if self.report == other.report:
            return True
        else:
            return False

    def __add__(self, other):
        """ Override the + operator. """
        
        return self.__add(other)

    def __pow__(self, power):
        """ Override the ** operator (power). """
        
        if power == 1:
            return self
        else:
            result = Polynomial._pow(self, self)
            for i in range(2, power):
                result = Polynomial._pow(self, result)         
            return result
  
def test():
    """ tests for Polynomial class. """
    
    assert str(Polynomial(0,1,0,-1,4,-2,0,1,3,0)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial([-5,1,0,-1,4,-2,0,1,3,0])) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x - 5"
    assert str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3= -1, x1=1)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    print(str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3= -1, x1=1).derivative().at_value(5)))
    assert str(Polynomial(x2=0)) == "0"
    assert str(Polynomial(x0=0)) == "0"
    assert Polynomial(x0=2, x1=0, x3=0, x2=3) == Polynomial(2,0,3)
    assert Polynomial(x2=0) == Polynomial(x0=0)
    assert str(Polynomial(x0=1)+Polynomial(x1=1)) == "x + 1"
    assert str(Polynomial([-1,1,1,0])+Polynomial(1,-1,1)) == "2x^2"
    pol1 = Polynomial(x2=3, x0=1)
    pol2 = Polynomial(x1=1, x3=0)
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(Polynomial(x0=-1,x1=1)**1) == "x - 1"
    assert str(Polynomial(x0=-1,x1=1)**2) == "x^2 - 2x + 1"
    pol3 = Polynomial(x0=-1,x1=1)
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(Polynomial(x0=2).derivative()) == "0"
    assert str(Polynomial(x3=2,x1=3,x0=2).derivative()) == "6x^2 + 3"
    assert str(Polynomial(x3=2,x1=3,x0=2).derivative().derivative()) == "12x"
    pol4 = Polynomial(x3=2,x1=3,x0=2)
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert Polynomial(-2,3,4,-5).at_value(0) == -2
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3) == 20
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3,5) == 44
    pol5 = Polynomial([1,0,-2])
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-1,3.6) == -23.92
    assert pol5.at_value(-1,3.6) == -23.92

if __name__ == '__main__':
    test()