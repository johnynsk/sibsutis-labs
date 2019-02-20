<?php

namespace Project\Exception;

class UnspecifiedParameter extends Client
{
    public function __construct($parameterName)
    {
        parent::__construct("You have not specified the mandatory \"${parameterName}\" parameter.");
    }
}
