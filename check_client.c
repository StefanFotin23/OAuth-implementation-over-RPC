/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "check.h"

#define LINE_MAX_SIZE 128
#define WORD_SIZE 16
#define DELIMITER ","
#define REQUEST "REQUEST"
#define READ "READ"
#define MODIFY "MODIFY"
#define DELETE "DELETE"
#define EXECUTE "EXECUTE"
#define INSERT "INSERT"
#define REQUEST "REQUEST"
#define REQUEST_DENIED "REQUEST_DENIED"
#define USER_NOT_FOUND "USER_NOT_FOUND"
#define OK "OK"

// REQUEST
void process_request(CLIENT *clnt, char *client_id, int refresh_duration) {
	// Request Authorization
	char **auth_token_aux = request_authorization_1(&client_id, clnt);
	if (auth_token_aux == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	char *auth_token = *auth_token_aux;
	
	if (strcmp(auth_token, USER_NOT_FOUND) == 0) {
		printf(USER_NOT_FOUND);
		printf("\n");
		return;
	}

	// Approve Request Token
	char **signed_auth_token_aux = approve_request_token_1(&auth_token, clnt);
	if (signed_auth_token_aux == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	char* signed_auth_token = *signed_auth_token_aux;
	
	// Request Access Token
	struct request_access_token_input req_acc_token_in;
	req_acc_token_in.auth_token = signed_auth_token;
	req_acc_token_in.client_id = client_id;
	req_acc_token_in.refresh_duration = refresh_duration;
	
	printf("Approve Request Token 2\n");
	struct request_access_token_output *req_acc_token_out = request_access_token_1(&req_acc_token_in, clnt);
	if (req_acc_token_out == (struct request_access_token_output *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	if (strcmp(req_acc_token_out->request_response, OK) != 0) {
		printf("  %s\n", req_acc_token_out->request_response);
	} else {
		printf("%s -> %s\n", auth_token, req_acc_token_out->resource_access_token);
	}
}

int
main (int argc, char *argv[])
{
	if (argc < 3) {
		printf ("usage: %s server_address input_file_path\n", argv[0]);
		exit (1);
	}
	char *server_address = argv[1];
	char *inputFile = argv[2];

	// Init host (server address) and client for RPC
	CLIENT *clnt = clnt_create (server_address, CHECKPROG, CHECKVERS, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (server_address);
		printf("Error occured creating client to communicate with server=%s\n", server_address);
		exit (1);
	}

	// Open the file for reading
    FILE *file = fopen(inputFile, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;  // Return an error code
    }

    // Read and print each line from the file
    char line[LINE_MAX_SIZE];  // Adjust the buffer size as needed
    while (fgets(line, sizeof(line), file) != NULL) {
        // Process each line as needed
		char client_id[WORD_SIZE];
		char operation[WORD_SIZE];
		char duration_string[WORD_SIZE];
		int token_duration;
		strcpy(client_id, strtok(line, DELIMITER));
		strcpy(operation, strtok(NULL, DELIMITER));
		strcpy(duration_string, strtok(NULL, DELIMITER));
		token_duration = atoi(duration_string);

		if (strcmp(operation, REQUEST) == 0) {
			process_request(clnt, client_id, token_duration);
		} else if (
			strcmp(operation, READ) == 0 ||
			strcmp(operation, MODIFY) == 0 ||
			strcmp(operation, DELETE) == 0 ||
			strcmp(operation, EXECUTE) == 0 ||
			strcmp(operation, INSERT) == 0 ||
			strcmp(operation, READ) == 0)
		{
			// OPERATIONS
			// Validate Delegated Action
			struct validate_delegated_action_input validate_delegated_action_1_arg;
			char **request_response_aux = validate_delegated_action_1(&validate_delegated_action_1_arg, clnt);
			if (request_response_aux == (char **) NULL) {
				clnt_perror (clnt, "call failed");
			}
			char *request_response = (char*) &request_response_aux;
		} else {
			printf("Operation=%s unexpected!", operation);
		}
    }	

	// Before exiting program
    fclose(file);
	clnt_destroy (clnt);
	exit (0);
}