// designPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <string>


namespace buidler 
{
    class HTMLPage
    {
    public:
        void setHeader(const std::string& header)
        {
            m_header = header;
        }

        void setPathNavigator(const std::string& pathNavigator)
        {
            m_pathNavigator = pathNavigator;
        }

        void setTitle(const std::string& title)
        {
            m_title = title;
        }

        void setWhat(const std::string& what)
        {
            m_what = what;
        }

        void setWhy(const std::string& why)
        {
            m_why = why;
        }

        void setWhen(const std::string& when)
        {
            m_when = when;
        }

        void setRouterOutlet(const std::string& routerOutlet)
        {
            m_router_outlet = routerOutlet;
        }

        

        void printHtml() const
        {
            std::cout << "HTML Page with: " << m_header << " HEADER" << m_pathNavigator << " PATH_NAVIGATOR"
                << m_title << " TITLE" << m_what << " WHAT" << m_why << " WHY" << m_when << " WHEN" <<
                m_router_outlet << " ROUTER_OUTLET" << std::endl;
        }
    private:
        std::string m_header;
        std::string m_pathNavigator;
        std::string m_title;
        std::string m_what;
        std::string m_why;
        std::string m_when;
        std::string m_router_outlet;

    };

    //ABSTRACT BUILDER CLASS
    class HTMLBuilder 
    {
    public:
        virtual ~HTMLBuilder() {} //Makes sure the appropriate destructor gets called when using polymorphism

        HTMLPage* getHTMLPage()
        {
            return m_HTMLPage.get();
        }

        void createNewHTMLPage()
        {
            m_HTMLPage = std::make_unique<HTMLPage>();
        }

        /*Abstract functions that will be later on overwritten*/
        virtual void buildHeader() = 0;
        virtual void buildPathNavigator() = 0;
        virtual void buildTitle() = 0;
        virtual void buildWhat() = 0;
        virtual void buildWhy() = 0;
        virtual void buildWhen() = 0;
        virtual void buildRouterOutlet() = 0;

    protected:
        std::unique_ptr<HTMLPage> m_HTMLPage; // pointer to an HTML page.
         
    };

    //---
    class ProjectPageBuilder : public HTMLBuilder
    {
         public:
             virtual ~ProjectPageBuilder() {};


            
    };
}

int main()
{
    std::cout << "Hello World!\n";
}


