#include "weakform/weakform.h"
#include "integrals/integrals_h1.h"
#include "boundaryconditions/essential_bcs.h"
#include "weakform/sample_weak_forms.h"

class MyWeakFormPoisson : public WeakFormLaplace
{
public:
  MyWeakFormPoisson(double const_f) : WeakFormLaplace() {
    VectorFormConstant* my_vector_form = new VectorFormConstant(0);
    my_vector_form->param.push_back(const_f);
    add_vector_form(my_vector_form);
  };
};

class EssentialBCNonConstant : public EssentialBC {
public:
  EssentialBCNonConstant(std::string marker, double const_f) 
           : EssentialBC(marker), const_f(const_f) { }

  ~EssentialBCNonConstant() { }

  inline EssentialBCValueType get_value_type() const { return EssentialBC::BC_FUNCTION; }

  scalar function(double x, double y) const {
    return (-const_f/4.0)*(x*x + y*y);
  }

  // Member.
  double const_f;
};