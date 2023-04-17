SOLVERFACTORY (!)

SPECIFICARE TOLLERANZE

COSTRUTTORE NELLA ABSTRACT CLASS

QUALI MEMBRI METTERE NELLA BASE CLASS

BISECTION: CAMBIA CONTROLLO DA CERR AD ASSERT

AGGIUNGI CHECK SU DATI IN INPUT... USA TEMPLATES E CONCEPTS?

Maybe you want to use bracketInterval to make sure that the interval passed to the bisection does indeed 
bracket a zero. Beware however that in this case you need to do something to handle the situation when the 
function is not crossing the zero and the user by mistake has asked, for instance, to use bisection.
