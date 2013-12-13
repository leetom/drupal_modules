(function($){

Drupal.ajax.prototype.beforeSubmit = function (form_values, element, options) {

    //若一个值设置未空，择后边的值也应该删除
    var field = ['field_address_province', 'field_address_city', 'field_address_county', 'field_address_detail'];
    var index = [];
    var filter_values = [];
    for(var j=0;j<field.length;j++){
        for(var i=0;i<form_values.length;i++){
           if(form_values[i].name == field[j]){
               index.push(i);
               filter_values.push(form_values[i].value);
               break;
           }
        }
    }
    var reset_follower = function(idx){
        for(var i=idx+1;i<field.length;i++){
            form_values[index[i]].value = '';
        }
    }
    for(var i=0;i<filter_values.length;i++){
        if(filter_values[i] == ''){
            console.log(field[i] + 'is empty!');
            for(var j=i;j<filter_values.length;j++){
                form_values[index[j]]='';
            }
            break;
        }
    }
    $('#edit-form-information option').each(function(){
         form_values.push({'name':$(this).val(),'value':$(this).text()});
     });
}

$(function(){
    var stopAjax = function(e){
        var $this = $(this);
        console.log($this.val());
        if($this.val() === ''){
            $(this).parents(".views-exposed-widget").nextAll(".views-exposed-widget").find('.form-select:enabled').html("<option value=''>请选择</option>");
        }
    };
    $("#views-exposed-form-team-page .form-select").on('change', stopAjax);
});

})(jQuery);
