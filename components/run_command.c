void run_command(){
	FILE *fp = popen(COMMAND_NAME,"r");
	char buffer[256];
	while (fgets(buffer, sizeof(buffer), fp)) {
		printf("%s", buffer);
	}
	pclose(fp);   
}
