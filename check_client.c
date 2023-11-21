/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "check.h"


void
checkprog_1(char *host)
{
	CLIENT *clnt;
	char * *result_1;
	char * request_authorization_1_arg;
	struct request_access_token_output  *result_2;
	struct request_access_token_input  request_access_token_1_arg;
	char * *result_3;
	struct validate_delegated_action_input  validate_delegated_action_1_arg;
	char * *result_4;
	char * approve_request_token_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, CHECKPROG, CHECKVERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = request_authorization_1(&request_authorization_1_arg, clnt);
	if (result_1 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = request_access_token_1(&request_access_token_1_arg, clnt);
	if (result_2 == (struct request_access_token_output *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = validate_delegated_action_1(&validate_delegated_action_1_arg, clnt);
	if (result_3 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = approve_request_token_1(&approve_request_token_1_arg, clnt);
	if (result_4 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	/*
	// Init host (server address) and client for RPC
	char *host = "127.0.0.1";
	CLIENT *clnt = clnt_create (host, CHECKPROG, CHECKVERS, "tcp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		printf("Error occured creating client to communicate with server=%s\n", host);
		exit (1);
	}

	// REQUEST
	// Request Authorization
	char **client_id;
	char **auth_token = request_authorization_1(&client_id, clnt);
	if (auth_token == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}

	// Approve Request Token
	char **signed_auth_token = approve_request_token_1(&auth_token, clnt);
	if (signed_auth_token == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}

	// Request Access Token
	struct request_access_token_input *req_acc_token_in;
	struct request_access_token_output *req_acc_token_out = request_access_token_1(&req_acc_token_in, clnt);
	if (req_acc_token_out == (struct request_access_token_output *) NULL) {
		clnt_perror (clnt, "call failed");
	}

	// OPERATIONS
	// Validate Delegated Action
	struct validate_delegated_action_input *validate_delegated_action_1_arg;
	char **request_response = validate_delegated_action_1(&validate_delegated_action_1_arg, clnt);
	if (request_response == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}

	// Before exiting program
	clnt_destroy (clnt);
	*/
	exit (0);
}

