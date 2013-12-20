#ifndef Manager_h
#define Manager_h


class Manager {

	public:
		Manager();
		~Manager();
		bool operator=();
		int getExperience();
		void setExperience();

	private:
		int experience;

};

#endif // Manager_h
