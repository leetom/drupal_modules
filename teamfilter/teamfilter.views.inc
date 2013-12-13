<?php

function teamfilter_views_query_alter(&$view, &$query){
    //修改team页的filter, 将输入的地名转换成id,并考虑结果不唯一的情况
    if($view->name == 'team' && $view->current_display == 'page'){
        foreach ($query->where as &$condition_group){
            foreach ($condition_group['conditions'] as &$condition){
                $address_array = array(
                    'field_data_field_address.field_address_province',
                    'field_data_field_address.field_address_city',
                    'field_data_field_address.field_address_country',
                );  //将名称转换为id的字段

                $field = $condition['field'];

                if ( in_array($field, $address_array)){
                    $name = $condition['value'];
                    $sql = 'SELECT `region_id` FROM {china_address} WHERE `region_name` like :region_name';
                    $result = db_query($sql, array(':region_name' => db_like($name) . "%"));

                    $count = $result->rowCount();
                    if($count < 1){
                        //没有符合
                        $conditioin['value'] = 'NaN';
                    }else if($count == 1 ){
                        // 只有一个符合,用等于
                        $region = $result->fetchColumn(0);  //the first column is the region_id
                        $condition['value'] = $region;
                    }else if($count > 1){
                        //很多符合,即搜索的形式
                        $region = $result->fetchAll(PDO::FETCH_COLUMN, 0); // 取得所有的第一列,即region_id
                        $condition = array(
                            'field' => $field,
                            'value' => $region,
                            'operator' => 'in',
                        );
                    }
                }elseif ($field == 'field_data_field_address.field_address_detail'){
                    $condition = array(
                        'field' => 'field_data_field_address.field_address_detail',
                        'value' => '%' . db_like($condition['value']) . '%',
                        'operator' => 'LIKE',
                    );
                }
            }
        }
    }
    

}

