double my_atof(char *str);
int square(int num, int exp);


int square(int num, int exp) {
    int og_num = num;

    if (exp == 0) {
        return 1;
    }

    while (exp != 1) {
        num = num*og_num;
        exp--;
    }
    return num;
}


double my_atof(char *str)
{
    double res = 0;
    int modifier = 1;

    if(*str == '-'){
        modifier = -1;
        str++;
    }
    while (*str != '\0') {

        if (*str == '.') {
            int num_decimals = 0;
            double decimal_res = 0;
            str++;

            while (*str != '\0') {
                decimal_res = decimal_res * 10 + (*str - '0');
                num_decimals++;
                str++;
            }
            res += decimal_res / square(10, num_decimals);
            return res * modifier;
        }

        res = 10 * res + (*str - '0');
        str++;
    }
    return res * modifier;
}