#include "pch.h"

#include <iostream>

#include <algorithm>
#include <iterator>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>

using boost::uuids::detail::md5;
using namespace std;


/*
*
*/
int MD5Init	(
			md5		*hash
			)
{

	hash = new md5();

	// **** inform the caller what went on ****
	return 0;
}


/*
*
*/
int MD5Final	(
				md5		*hash
				)
{

	// **** inform the caller what went on ****
	return 0;
}


/*
*
*/
int MD5Update	(
				md5		*hash,
				string	str
				)
{
	hash->process_bytes(str.data(), str.size());

	// **** inform the caller what went on ****
	return 0;
}


/*
*
*/
int	MD5Final	(
				md5					*hash,
				md5::digest_type	*digest
				)
{
	hash->get_digest(*digest);

	// **** inform the caller what went on ****
	return 0;
}


/*
* Convert MD5 digest to string.
*/
int MD5DigestToString	(
						const md5::digest_type	&digest,
						string					&digestStr
						)
{

	// **** ****
	digestStr = "";

	// **** convert to char[] ****
	const auto charDigest = reinterpret_cast<const char *>(&digest);

	// **** convert char[] digest to string ****
	boost::algorithm::hex(charDigest, charDigest + sizeof(md5::digest_type), std::back_inserter(digestStr));

	// ???? ????
	cout << "MD5DigestToString <<< digestString ==>" << digestStr << "<==" << endl;

	// **** inform the caller what went on ****
	return 0;
}


/*
* Basic test to verify MD5 operation.
*/
void basicTest() {

	// **** general purpose string ****
	string	str;
	string	digestStr = "";

	// **** prompt for first string ****
	cout << "basicTest >>> str: ";

	// **** loop processing input ****
	while (getline(cin, str)) {

		// **** check if we are done ****
		if (str.compare(string("-1")) == 0) {
			break;
		}

		// **** display string ****
		cout << "basicTest <<< str ==>" << str << "<==\n";

		// **** generate a MD5 digest ****
		md5					hash;
		md5::digest_type	digest;

		hash.process_bytes(str.data(), str.size());
		hash.get_digest(digest);

		// **** convert to string and display MD5 digest ****
		MD5DigestToString(	digest,
							digestStr);
		cout << "basicTest <<< digestStr ==>" << digestStr << "<==\n";

		// **** prompt for next string to process ****
		cout << "basicTest >>> str [-1 to exit]: ";
	}
}


/*
* Test scaffolding.
*/
int main()
{

	bool				done;									// done looping flag

	char				buffer[BUFSIZ];							// general purpose buffer

	md5::digest_type	digest;									// MD5 digest

	int					retVal,									// returned by this function
						selection,								// user selection
						status;									// returned by function calls

	md5					hash;									// MD5 hash

	string				digestStr,								// digest string
						str;									// string

	// **** initialization ****
	retVal		= 0;											// hope all goes well

	digestStr	= "";											// for starters
	done		= false;										// for starters
	selection	= 1;											// for starters

	memset((void *)buffer, (int)0x00, sizeof(buffer));

	// **** welcome message ****
	cout << "**** MD5 using Boost C++ Libraries ****\n";

	// **** loop testing functions ****
	do {

		// **** display menu ****
		printf("\n");
		printf("1\tbasicTest()\n");

		printf("\n");
		printf("2\tMD5Init()\n");
		printf("3\tMD5Update()\n");
		printf("4\tMD5Final()\n");
		printf("5\tMD5DigestToString()\n");

		printf("\n");
		printf("-1\tQUIT\n");

		// **** prompt and get user selection ****
		printf("\n>>> selection [%d]: ", selection);
		fgets(	buffer,
				BUFSIZ,
				stdin);
		buffer[strlen(buffer) - 1] = '\0';
		if (buffer[0] != '\0')
			selection = atoi(buffer);

		// **** process user selection ****
		switch (selection) {
		case -1:
			done = true;
			break;

		case 1:
			basicTest();
			break;

		case 2:
			status = MD5Init(&hash);
			break;

		case 3:
			str = "hello world";
			status = MD5Update(	&hash,
								str);
			break;

		case 4:
			status = MD5Final(	&hash,
								&digest);
			break;

		case 5:
			status = MD5DigestToString(	digest,
										digestStr);

			// ???? ????
			cout << "main <<< digestStr =>" << digestStr << "<==\n";
			break;

		default:
			printf("main <<< invalid selection: %d\n", selection);
			break;
		}
	} while (!done);

	// **** clean up ****
done:

	// **** inform caller what went on ****
	return retVal;
}
