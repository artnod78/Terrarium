#ifndef CompteurFloat_h
#define CompteurFloat_h

class CompteurFloat
{
	public:
		CompteurFloat(float value = 0);
		void	start(float value = 0);
		
		void	run(int key);
		
		float	value(void);
		int		entier(void);
		int		decimal(void);
		bool	isSelect(void);
		
		bool	selected(void);		
		
	private:		
		int		_entier;
		int		_decimal;
		bool	_isSelect;		
		bool	_selected;
};
#endif
