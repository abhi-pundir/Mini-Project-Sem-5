
void pass_2()
{
    int start_add, i,locctr,address,flag,length,val,optab_val,symtab_val;
    char opcode[20],label[20],check[20],count[20];

    FILE *fp1,*fp2,*fp3,*fp4;
    fp1=fopen("intermediate.txt","r");
    fp4=fopen("output.txt","w");

    fscanf(fp1,"%s %s %X",&label,&opcode,&start_add);
    fprintf(fp4,"%s\t%s\t%X\n",label,opcode,start_add);

}





