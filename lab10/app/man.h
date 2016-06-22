#ifndef PROJECT_APP_MAN
#define PROJECT_APP_MAN

class App_Man {
    public:
        void read();
        char* getSurname();
        int getNumber();
        int getPoints();

    private:
        char surname[64];
        int number;
        int points;
};

#endif

