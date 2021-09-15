//edited by davidrs3, airra2, nrgoer5
#include "ComplexNumber.h"
#include "helper.h"
#include <cmath>

ComplexNumber::ComplexNumber()
{
    /* Your code here */
    real_component = 0.0;
    imaginary_component = 0.0;
    magnitude = 0.0;
    phase = 0.0;
    number_type = COMPLEX;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    /* Your code here */
    real_component = rval_real_component;
    imaginary_component = rval_imaginary_component;
    double real_square = real_component * real_component;
    double imaginary_square = imaginary_component * imaginary_component;
    double sum_square = real_square + imaginary_square;
    magnitude = sqrt(sum_square);
    phase = calculate_phase(rval_real_component, rval_imaginary_component);
    number_type = COMPLEX;

}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    /* Your code here */
    real_component = other.get_real_component();
    imaginary_component = other.get_imaginary_component();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    number_type = COMPLEX;
}

void ComplexNumber::set_real_component (double rval)
{
    /* Your code here */
    real_component = rval;
    double real_square = real_component * real_component;
    double imaginary_square = imaginary_component * imaginary_component;
    double sum_square = real_square + imaginary_square;
    magnitude = sqrt(sum_square);
    phase = calculate_phase(real_component, imaginary_component);
    return;
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
    imaginary_component = rval;
    double real_square = real_component * real_component;
    double imaginary_square = imaginary_component * imaginary_component;
    double sum_square = real_square + imaginary_square;
    magnitude = sqrt(sum_square);
    phase = calculate_phase(real_component, imaginary_component);
    return;
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component + arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component - arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    double realtoreal = real_component * arg.get_real_component();
    double realtoimag = real_component * arg.get_imaginary_component();
    double imagtoreal = imaginary_component * arg.get_real_component();
    double imagtoimag = -(imaginary_component * arg.get_imaginary_component());

    return ComplexNumber(realtoreal, realtoimag) + ComplexNumber(imagtoimag, imagtoreal);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /*double realtoreal = real_component * arg.get_real_component();
    double imagtoimag = imaginary_component * arg.get_imaginary_component();
    double imagtoreal = imaginary_component * arg.get_real_component();
    double realtoimag = real_component * arg.get_imaginary_component();
    double argrealsquare = arg.get_real_component() * arg.get_real_component();
    double argimagsquare = arg.get_imaginary_component() * arg.get_imaginary_component();
    //real * real - imag * imag / csquared + dsquared
    //imaginary * real - a * d / cquared + dsquared
    //first comment is real, second comment is imaginary*/
    double real1 = real_component * arg.get_real_component();
    double real2 = imaginary_component * arg.get_imaginary_component();
    double imag1 = imaginary_component * arg.get_real_component();
    double imag2 = real_component * arg.get_imaginary_component();
    double denom1 = arg.get_imaginary_component() * arg.get_imaginary_component();
    double denom2 = arg.get_real_component() * arg.get_real_component();
    double denom = denom1 + denom2;
    double numreal = real1+real2;
    double numimag = imag1 - imag2;
    double finreal = numreal / denom;
    double finimag = numimag / denom;
    return ComplexNumber(finreal, finimag);
    //return (ComplexNumber(realtoreal, imagtoimag) + ComplexNumber(imagtoreal, realtoimag)) / ComplexNumber(argrealsquare, argimagsquare);
    //return ComplexNumber(topreal, bottomimag);
    //return ComplexNumber(endreal, endimag);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component + arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component - arg.get_real_component(), imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component * arg.get_real_component(), imaginary_component * arg.get_real_component());
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component / arg.get_real_component(), imaginary_component / arg.get_real_component());
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component, imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    //double realximag = real_component * arg.get_imaginary_component();
    //double imagximag = imaginary_component * arg.get_imaginary_component();
	//return ComplexNumber(imagximag, realximag);
    ComplexNumber imag = ComplexNumber(0.0, arg.get_imaginary_component());
    ComplexNumber operate = ComplexNumber(real_component, imaginary_component);
    ComplexNumber result = ComplexNumber();
    result = operate * imag;
    return result;
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    ComplexNumber operate = ComplexNumber(real_component, imaginary_component);
    //double realdivimag = real_component / arg.get_imaginary_component();
    //double imagdivimag = imaginary_component / arg.get_imaginary_component();
	//return ComplexNumber(imagdivimag, realdivimag);
    ComplexNumber imag = ComplexNumber(0.0, arg.get_imaginary_component());
    ComplexNumber result = ComplexNumber();
    result = operate / imag;
    return result;
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}