window.onload = function() {
    
    let colors = ["#B22222", "Blue", "#1F5F7A", "#556B2F", "Red", "#CD5C5C", "DeepPink", "Black","#BDB76B", "#696969", "DarkGoldenRod", "DarkOrchid","DarkOrange", "#CD853F", "Green", "#FFC300", "#FF6E6E", "#766738", "#387659", "#9800C0"];
   // let colors = ["DeepPink", "Blue", "Chartreuse", "Red", "Aqua", "Brown", "Aquamarine", "Black", "Cyan", "DarkGoldenRod", "DarkOrchid","DarkOrange", "Gold", "Green", "GreenYellow"];
    let courses = ['NURS2004', 'NURS2009', 'NURS2011', 'NURS2013', 'NURS3009', 'NURS3010', 'NURS3011', 'NURS3028', 'NURS3029', 'NURS3030', 'NURS4000', 'NURS4001', 'NURS4002', 'NURS4066', 'NURS4067', 'NURS2000', 'NURS2002', 'NURS5005', 'NURS5226', 'NURS2003'];

    let eventBorder = document.getElementsByClassName("calendar monthview");
    let output;
    for (output = 0; output < eventBorder.length; output++) {
        if(eventBorder[output].querySelectorAll("span.field-content")[0]) {
        var courseName = eventBorder[output].querySelectorAll("span.field-content")[0].getElementsByTagName("a")[0].innerHTML;
        if (checkValue(courseName, courses) === 'Exist')
        {
            
            eventBorder[output].querySelectorAll("span.field-content")[0].getElementsByTagName("a")[0].setAttribute("style", "color: " + colors[courses.indexOf(courseName.substr(0, 8))] + " !important");
            eventBorder[output].style.borderLeft = "4px solid " + colors[courses.indexOf(courseName.substr(0, 8))];

        }
    }
    
    }
};
function checkValue(value,arr){
    var status = 'Not exist';

    for(var i=0; i<arr.length; i++){
        var name = arr[i];
        if(value.indexOf(name) > -1){
            status = 'Exist';
            break;
        }
    }

    return status;
}

