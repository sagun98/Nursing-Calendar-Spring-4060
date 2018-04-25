window.onload = function() 
{

    let courseColors = ["#B22222", "Blue", "#1F5F7A", "#556B2F", "Red", "#CD5C5C", "Brown", "Black","#BDB76B", "#696969", "DarkGoldenRod", "DarkOrchid","DarkOrange", "#CD853F", "Green", "#FFC300", "#FF6E6E", "#766738", "#387659", "#9800C0"];
    let courseNames = ['NURS2004', 'NURS2009', 'NURS2011', 'NURS2013', 'NURS3009', 'NURS3010', 'NURS3011', 'NURS3028', 'NURS3029', 'NURS3030', 'NURS4000', 'NURS4001', 'NURS4002', 'NURS4066', 'NURS4067', 'NURS2000', 'NURS2002', 'NURS5005', 'NURS5226', 'NURS2003'];

    //Select all <span class="field-content"> tags
    let initialTag = document.querySelectorAll("span.field-content");
    
    //Selects every event on the calendar with the class name "calendar monthview"
    let borderHTMLClass = document.getElementsByClassName("calendar monthview");
    //counts the actual number of events that were given a color
    let eventCount = 0;

    //For each <span class="field-content"> tag select the first <a> tag
    for (let count = 0; count < initialTag.length; count++) 
    {
        //Select the all <a> tags inside of <span class="field-content">
        var aTag = initialTag[count].getElementsByTagName("a");
        //Copy the innerHTML of the first <a> tag since it should contain the course name
        var htmlCourseName = aTag[0].innerHTML;

        //Apply the designated color to the <a> tag thus changing the color of the course name on the calendar
        //First check if the htmlCourseName exists in the preset courseNames array
        if (checkValue(htmlCourseName, courseNames) === 'Exist')
        {
            aTag[0].setAttribute("style", "color: " + courseColors[courseNames.indexOf(htmlCourseName)] + " !important");
            
            let aTagChecker = borderHTMLClass[eventCount].getElementsByTagName("a");
            for(let i = 0; i < borderHTMLClass.length; i++)
                if(borderHTMLClass[i].querySelectorAll("span.field-content")[0])
                    console.log(borderHTMLClass[i].querySelectorAll("span.field-content")[0].getElementsByTagName("a")[0].innerHTML);
            if (checkValue(aTagChecker[0].innerHTML, courseNames) === 'Exist')
            
            {

                borderHTMLClass[eventCount].style.borderLeft = "4px solid " + courseColors[courseNames.indexOf(htmlCourseName)];
               // aTag[eventCount].style.borderLeft = "4px solid " + courseColors[courseNames.indexOf(htmlCourseName)];
                
                
            } 
            eventCount++;
            
        }
    }

};

    
//Checks if a value is in an array
//If there is a value it returns 'Exists'
function checkValue(value,arr){
    var status = 'Not exist';

    for(var i=0; i<arr.length; i++){
        var name = arr[i];
        if(name === value){
            status = 'Exist';
            break;
        }
    }

    return status;
}

