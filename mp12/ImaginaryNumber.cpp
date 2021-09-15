//edited by davidrs3, airra2, nroger5
#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
    /* Your code here */
    imaginary_component = 0.0;
    magnitude = 0.0;
    phase = 0.0;
    number_type = IMAGINARY;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    /* Your code here */
    imaginary_component = rval;
    magnitude = abs(imaginary_component);
    phase = calculate_phase(0.0, rval);
    number_type = IMAGINARY;
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    /* Your code here */
    imaginary_component = other.get_imaginary_component();
    magnitude = other.get_magnitude();
    phase = other.get_phase();
    number_type = IMAGINARY;
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    /* Your code here */
    imaginary_component = rval;
    magnitude = abs(imaginary_component);
    phase = calculate_phase(0.0, rval);
    return;
}

double ImaginaryNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    /* Your code here */
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component + arg.get_imaginary_component());
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component - arg.get_imaginary_component());
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    //return RealNumber(imaginary_component * arg.get_imaginary_component());
    return RealNumber(imaginary_component * arg.get_magnitude());
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(imaginary_component / arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    double negarg = 0 - arg.get_real_component();
    return ComplexNumber(negarg, imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component * arg.get_real_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component / arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */

    return ComplexNumber(arg.get_real_component(), imaginary_component + arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    //the abs is the change
    return ComplexNumber(-arg.get_real_component(), imaginary_component - arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    
    //return ComplexNumber(imaginary_component * arg.get_imaginary_component(), imaginary_component * arg.get_real_component());
    //return ComplexNumber(imaginary_component * abs(arg.get_imaginary_component()), imaginary_component * arg.get_real_component());
    ComplexNumber imag = ComplexNumber(0.0, imaginary_component);
    ComplexNumber product = ComplexNumber();
    product = imag * arg;
    return product;
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    //return ComplexNumber(imaginary_component / arg.get_imaginary_component(), imaginary_component / arg.get_real_component());
    ComplexNumber imag = ComplexNumber(0.0, imaginary_component);
    ComplexNumber quotient = ComplexNumber();
    quotient = imag / arg;
    return quotient;
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}