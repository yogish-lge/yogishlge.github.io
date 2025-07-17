//Copyright 2025 This is for testing the data of genrating the release notes
//The release notes are to be generated & posted for the testing purpose.

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <iostream>

XERCES_CPP_NAMESPACE_USE
//Test for the change -- Yogish 1
int main(int argc, char* argv[]) {
    try {
        XMLPlatformUtils::Initialize(); // Initialize Xerces-C++
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Error during Xerces-C++ initialization: " << message << std::endl;
        XMLString::release(&message);
        return 1;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Never); // No validation for simplicity
    parser->setDoNamespaces(false); // No namespace processing for simplicity

    const char* xmlFile = "example.xml"; // Replace with your XML file path

    try {
        parser->parse(xmlFile); // Parse the XML file
        DOMDocument* doc = parser->getDocument(); // Get the DOM document

        // Get the root element
        DOMElement* rootElement = doc->getDocumentElement();
        if (rootElement) {
            char* tagName = XMLString::transcode(rootElement->getTagName());
            std::cout << "Root element: " << tagName << std::endl;
            XMLString::release(&tagName);

            // Access child elements (example: iterating through children)
            DOMNodeList* children = rootElement->getChildNodes();
            for (XMLSize_t i = 0; i < children->getLength(); ++i) {
                DOMNode* child = children->item(i);
                if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
                    DOMElement* childElement = dynamic_cast<DOMElement*>(child);
                    char* childTagName = XMLString::transcode(childElement->getTagName());
                    std::cout << "  Child element: " << childTagName << std::endl;
                    XMLString::release(&childTagName);

                    // Access attributes (example: an attribute named "id")
                    if (childElement->hasAttribute(XMLString::transcode("id"))) {
                        char* idAttr = XMLString::transcode(childElement->getAttribute(XMLString::transcode("id")));
                        std::cout << "    Attribute 'id': " << idAttr << std::endl;
                        XMLString::release(&idAttr);
                    }

                    // Access text content
                    DOMNode* textNode = childElement->getFirstChild();
                    if (textNode && textNode->getNodeType() == DOMNode::TEXT_NODE) {
                        char* textContent = XMLString::transcode(textNode->getNodeValue());
                        std::cout << "    Text content: " << textContent << std::endl;
                        XMLString::release(&textContent);
                    }
                }
            }
        }
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Error during parsing: " << message << std::endl;
        XMLString::release(&message);
        return 1;
    } catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cerr << "Error during DOM operations: " << message << std::endl;
        XMLString::release(&message);
        return 1;
    }
   // Test of the Changes in : -- Yogish 2
    delete parser; // Clean up the parser
    XMLPlatformUtils::Terminate(); // Terminate Xerces-C++
    return 0;
}
