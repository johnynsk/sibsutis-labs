<?php

namespace Project;

class UnspecifiedParameter extends ClientException
{
    public function __construct($parameterName)
    {
        parent::__construct("You have not specified the mandatory \"${parameterName}\" parameter.");
    }
}
