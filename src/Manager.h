#ifndef Manager_h
#define Manager_h


class Manager {

	public:
		Manager();
		~Manager();
		Manager operator=();
		int getExperience();
		void setExperience();

	private:
		int experience;

};

#endif // Manager_h
