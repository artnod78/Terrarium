#ifndef CompteurSeconde_h
#define CompteurSeconde_h

class CompteurSeconde
{
	public:
		CompteurSeconde(unsigned long value = 0);
		void	start(unsigned long value = 0);
		
		void	run(int key);
		
		unsigned long seconde(void);
		bool	isSelect(void);
		
		int		increment(void);

	private:
		unsigned long _seconde;
		bool	_isSelect;
		int		_increment;
};
#endif
