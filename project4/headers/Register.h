#include <systemc.h>

template <int T> 
class dRegister : public sc_module {
public:
	sc_in <sc_logic> clk, rst, cen, zer;
	sc_in <sc_lv<T> > regin;
	sc_out <sc_lv<T> > regout;

	SC_HAS_PROCESS(dRegister);
	dRegister(sc_module_name);

	void registering();
};

template <int T>
dRegister<T>::dRegister(sc_module_name)
{
	SC_METHOD(registering);
	sensitive << clk << rst;
}

template <int T>
void dRegister<T>::registering()
{
	sc_lv<T> tmp;
	if (rst =='1')
	{
		for (int i =0; i <T; i++)
			tmp[i] = SC_LOGIC_0;
		regout = tmp;
	}
	else if ((clk->event()) && (clk == '1')){
		if (cen == '1') {
			if (zer == '1') {
				for (int i = 0; i < T; i++)
					tmp[i] = SC_LOGIC_0;
				regout = tmp;
			}
			else regout = regin;
		}
	}
};
