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
#define REQUEST_DENIED "REQUEST_DENIED"
#define USER_NOT_FOUND "USER_NOT_FOUND"
#define OK "OK"

// REQUEST
char* process_request(CLIENT *clnt, char *client_id, int refresh_duration) {
	// Request Authorization
	char **auth_token_aux = request_authorization_1(&client_id, clnt);
	if (auth_token_aux == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	char *auth_token = *auth_token_aux;
	
	if (strcmp(auth_token, USER_NOT_FOUND) == 0) {
		printf(USER_NOT_FOUND);
		printf("\n");
		return USER_NOT_FOUND;
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

	struct request_access_token_output *req_acc_token_out = request_access_token_1(&req_acc_token_in, clnt);
	if (req_acc_token_out == (struct request_access_token_output *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	if (strcmp(req_acc_token_out->request_response, OK) == 0) {
		printf("%s -> %s\n", auth_token, req_acc_token_out->resource_access_token);
	} else {
		printf("%s\n", req_acc_token_out->request_response);
	}
	return req_acc_token_out->resource_access_token;
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
	char resource_access_token[16];

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
		char last_input_field[WORD_SIZE];
		int token_duration;
		strcpy(client_id, strtok(line, DELIMITER));
		strcpy(operation, strtok(NULL, DELIMITER));
		strcpy(last_input_field, strtok(NULL, DELIMITER)); // it is either the token_duration or the resource used for operations

		if (strcmp(operation, REQUEST) == 0) {
			token_duration = atoi(last_input_field);
			strcpy(resource_access_token, process_request(clnt, client_id, token_duration));
		} else if (
			strcmp(operation, READ) == 0 ||
			strcmp(operation, MODIFY) == 0 ||
			strcmp(operation, DELETE) == 0 ||
			strcmp(operation, EXECUTE) == 0 ||
			strcmp(operation, INSERT) == 0)
		{
			// OPERATIONS
			// Validate Delegated Action
			struct validate_delegated_action_input validate_delegated_action_in;
			validate_delegated_action_in.resource_access_token = resource_access_token;
			validate_delegated_action_in.resource = last_input_field;
			validate_delegated_action_in.client_id = client_id;

			// Add to input the operation
			if (strcmp(operation, READ) == 0) {
				validate_delegated_action_in.operation = "R";
			} else if (strcmp(operation, MODIFY) == 0) {
				validate_delegated_action_in.operation = "M";
			} else if (strcmp(operation, DELETE) == 0) {
				validate_delegated_action_in.operation = "D";
			} else if (strcmp(operation, EXECUTE) == 0) {
				validate_delegated_action_in.operation = "X";
			} else if (strcmp(operation, INSERT) == 0) {
				validate_delegated_action_in.operation = "I";
			}

			char **request_response_aux = validate_delegated_action_1(&validate_delegated_action_in, clnt);
			if (request_response_aux == (char **) NULL) {
				clnt_perror (clnt, "call failed");
			}
			char *request_response = *request_response_aux;
			printf("%s\n", request_response);
		} else {
			printf("Operation=%s unexpected!", operation);
		}
    }	

	// Before exiting program
    fclose(file);
	clnt_destroy (clnt);
	exit (0);
}