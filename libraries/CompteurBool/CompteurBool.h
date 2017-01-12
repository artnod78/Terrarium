#ifndef CompteurBool_h
#define CompteurBool_h

class CompteurBool
{
	public:
		CompteurBool(bool value = false);
		void	start(bool value = false);
		
		void	run(int key);
		
		bool	value(void);
		bool	isSelect(void);

	private:		
		bool	_value;	
		bool	_isSelect;
};
#endif
