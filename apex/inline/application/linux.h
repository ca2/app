

int __main(int argc, char * argv[], char * envp[]);

int main(int argc, char * argv[], char * envp[])
{

   return __main(argc, argv, envp);

}


static const char * s_pszBinRelocInitGetSymbol = "br_init_get_symbol";


const char * br_init_get_symbol()
{

    return s_pszBinRelocInitGetSymbol;

}



