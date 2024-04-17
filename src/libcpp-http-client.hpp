/*

Modern non-blocking HTTP Client library for C++ (17+)
version 1.0.0
https://github.com/lk-libs/libcpp-http-client

If you encounter any issues, please submit a ticket at https://github.com/lk-libs/libcpp-http-client/issues

Copyright (c) 2024 lk-libs, Levent KARAGÖL

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef LIBCPP_HTTP_CLIENT_HPP
#define LIBCPP_HTTP_CLIENT_HPP

#include <iostream>
#include <string>
#include <functional>
#include <future>
#include <map>
#include <curl/curl.h>

namespace lklibs {

    /**
     * @brief Contains the result of HTTP requests
     */
    class HttpResult {
    public:
        /**
         * @brief Information on whether the request was successful or not
         */
        bool succeed = false;

        /**
         * @brief HTTP status code resulting from the request
         */
        int statusCode = 0;

        /**
         * @brief Text data received as a result of the request
         */
        std::string textData;

        /**
         * @brief Binary data received as a result of the request
         */
        std::vector<unsigned char> binaryData;

        /**
         * @brief Error message received as a result of the request
         */
        std::string errorMessage;

        HttpResult() = default;

        HttpResult(bool succeed, std::string textData, std::vector<unsigned char> binaryData, int statusCode, std::string errorMessage)
                : succeed(succeed), textData(std::move(textData)), binaryData(std::move(binaryData)), statusCode(statusCode), errorMessage(std::move(errorMessage)) {}
    };

    /**
     * @brief HTTP client class that makes asynchronous HTTP requests
     */
    class HttpClient {
    public:

        /**
         * @brief Makes an HTTP GET request for the given URL and returns the result
         *
         * @param url: Request URL
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> getRequest(const std::string &url) {

            return request(url, "GET", "", false, {});
        }

        /**
         * @brief Makes an HTTP GET request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> getRequest(const std::string &url, bool returnAsBinary) {

            return request(url, "GET", "", returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP GET request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> getRequest(const std::string &url, const std::map<std::string, std::string> &headers) {

            return request(url, "GET", "", false, headers);
        }

        /**
         * @brief Makes an HTTP GET request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> getRequest(const std::string &url, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "GET", "", returnAsBinary, headers);
        }


        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url) {

            return request(url, "POST", "", false, {});
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, const std::string &payload) {

            return request(url, "POST", payload, false, {});
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, bool returnAsBinary) {

            return request(url, "POST", "", returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, const std::map<std::string, std::string> &headers) {

            return request(url, "POST", "", false, headers);
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, const std::string &payload, bool returnAsBinary) {

            return request(url, "POST", payload, returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, const std::string &payload, const std::map<std::string, std::string> &headers) {

            return request(url, "POST", payload, false, headers);
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "POST", "", returnAsBinary, headers);
        }

        /**
         * @brief Makes an HTTP POST request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> postRequest(const std::string &url, const std::string &payload, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "POST", payload, returnAsBinary, headers);
        }


        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url) {

            return request(url, "PUT", "", false, {});
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, const std::string &payload) {

            return request(url, "PUT", payload, false, {});
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, bool returnAsBinary) {

            return request(url, "PUT", "", returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, const std::map<std::string, std::string> &headers) {

            return request(url, "PUT", "", false, headers);
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, const std::string &payload, bool returnAsBinary) {

            return request(url, "PUT", payload, returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, const std::string &payload, const std::map<std::string, std::string> &headers) {

            return request(url, "PUT", payload, false, headers);
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "PUT", "", returnAsBinary, headers);
        }

        /**
         * @brief Makes an HTTP PUT request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> putRequest(const std::string &url, const std::string &payload, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "PUT", payload, returnAsBinary, headers);
        }


        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url) {

            return request(url, "DELETE", "", false, {});
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, const std::string &payload) {

            return request(url, "DELETE", payload, false, {});
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, bool returnAsBinary) {

            return request(url, "DELETE", "", returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, const std::map<std::string, std::string> &headers) {

            return request(url, "DELETE", "", false, headers);
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, const std::string &payload, bool returnAsBinary) {

            return request(url, "DELETE", payload, returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, const std::string &payload, const std::map<std::string, std::string> &headers) {

            return request(url, "DELETE", payload, false, headers);
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "DELETE", "", returnAsBinary, headers);
        }

        /**
         * @brief Makes an HTTP DELETE request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param payload: Payload to be sent with the request (Optional)
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> deleteRequest(const std::string &url, const std::string &payload, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "DELETE", payload, returnAsBinary, headers);
        }


        /**
         * @brief Makes an HTTP PATCH request for the given URL and returns the result
         *
         * @param url: Request URL
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> patchRequest(const std::string &url) {

            return request(url, "PATCH", "", false, {});
        }

        /**
         * @brief Makes an HTTP PATCH request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> patchRequest(const std::string &url, bool returnAsBinary) {

            return request(url, "PATCH", "", returnAsBinary, {});
        }

        /**
         * @brief Makes an HTTP PATCH request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> patchRequest(const std::string &url, const std::map<std::string, std::string> &headers) {

            return request(url, "PATCH", "", false, headers);
        }

        /**
         * @brief Makes an HTTP PATCH request for the given URL and returns the result
         *
         * @param url: Request URL
         * @param returnAsBinary: Return result as binary instead of string (Optional)
         * @param headers: HTTP Header information to be sent when making the request (Optional)
         * @return Result of the request (see HttpResult object for details)
         */
        static std::future<HttpResult> patchRequest(const std::string &url, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return request(url, "PATCH", "", returnAsBinary, headers);
        }

    private:

        static std::future<HttpResult> request(const std::string &url, const std::string &method, const std::string &payload, bool returnAsBinary, const std::map<std::string, std::string> &headers) {

            return std::async(std::launch::async, [=]() -> HttpResult {

                CURL* curl;
                CURLcode res;
                struct curl_slist* headerList = nullptr;
                std::string stringBuffer;
                std::vector<unsigned char> binaryBuffer;
                int statusCode = 0;

                curl_global_init(CURL_GLOBAL_DEFAULT);
                curl = curl_easy_init();

                if (curl) {

                    for (const auto &header: headers) {

                        std::string headerStr = header.first + ": " + header.second;

                        headerList = curl_slist_append(headerList, headerStr.c_str());
                    }

                    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerList);
                    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

                    if ((method == "POST" || method == "PUT" || method == "DELETE") && !payload.empty()) {

                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
                    }

                    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());

                    if (returnAsBinary) {

                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, binaryWriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &binaryBuffer);

                    } else {

                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, textWriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stringBuffer);
                    }

                    res = curl_easy_perform(curl);

                    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &statusCode);

                    curl_easy_cleanup(curl);
                    curl_slist_free_all(headerList);

                    if (res == CURLE_OK && statusCode == 200) {

                        return {true, stringBuffer, binaryBuffer, statusCode, ""};

                    } else {

                        return {false, stringBuffer, binaryBuffer, statusCode, curl_easy_strerror(res)};
                    }
                }

                curl_global_cleanup();

                return {false, "", {}, 0, "CURL initialization failed"};
            });
        }

        static size_t textWriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {

            ((std::string*) userp)->append((char*) contents, size * nmemb);

            return size * nmemb;
        }

        static size_t binaryWriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {

            auto &buffer = *static_cast<std::vector<unsigned char>*>(userp);

            auto* data = static_cast<unsigned char*>(contents);

            buffer.insert(buffer.end(), data, data + size * nmemb);

            return size * nmemb;
        }
    };
}

#endif //LIBCPP_HTTP_CLIENT_HPP
